#include <Wire.h>
#include <iarduino_I2C_Bumper.h>
#include <Servo.h>
#include "GyverPID.h"
#include "buzzer.h"

iarduino_I2C_Bumper bum(0x09);
iarduino_I2C_Bumper bum1(0x08);
Servo servo;
Servo ESC;
GyverPID r(0.1, 0.01, 0.01, 1);

int encoder = 0;
int s = 0;
int deg = 0;
int ir = 0;
int out = 0;
bool left = false;
bool st = 0;
int ss;
int ts;
int trace;
int j = 0;
int se = 0;
unsigned long timing = 0;
int act_speed = 0;
int sspeed = 0;
int intens = 10;

bool vlevo = 0;
bool vpravo = 0;
bool vpered = 1;


void encoder_check() {
  if (Serial2.available()) {
    se = Serial2.parseInt();
    if (se != 0) {
      encoder = se;
    }
  }
  Serial.print("encoder: ");
  Serial.println(encoder);
}


void servo_pos(int degres) {
  degres = constrain(degres, -100, 100);
  degres = map(degres, -100, 100, 65, 115);
  if (vpravo) degres = constrain(degres, 98, 115);
  else if (vlevo) degres = constrain(degres, 65, 82);
  else if (vpered) degres = constrain(degres, 80, 100);
  servo.write(degres);
}

void set() {
  Serial.begin(9600);
  Serial1.begin(115200);
  Serial2.begin(115200);
  Wire.begin();

  bum.begin();
  bum1.begin();

  buz_begin();

  servo.attach(44);
  ESC.attach(45);

  r.setDirection(REVERSE);
  r.setLimits(-100, 100);
  r.setpoint = 0;
  beep();
}

void go(int need_speed, int intensivity) {
    if (act_speed < need_speed) {
      if (millis() - timing > map(intensivity, 1, 10, 75, 0)) {
        act_speed = s;
        s += 2;
        timing = millis();
      }
    }
    else if (act_speed > need_speed) {
      if (millis() - timing > map(intensivity, 1, 10, 75, 0)) {
        act_speed = s;
        s -= 2;
        timing = millis();
      }
    }
    ESC.writeMicroseconds(map(constrain(s, -100, 100), -100, 100, 1000, 2000));
}

float digital_sensors() {
  float a = bum.getErrPID();
  float b = bum1.getErrPID();
  out = map(a+b, -8.5, 8.5, -100, 100);
  return out;
}

float readlineRight(bool service = 0) {
  int sum = 0;
  for (int i = 1; i < 10; i++) {
    sum += bum1.getLineDigital(i);
  }
  if (service) Serial.println(sum);
  return sum;
}

float readline(bool service = 0) {
  int sum = 0;
  for (int i = 1; i < 10; i++) {
    sum += bum.getLineDigital(i);
  }
  for (int i = 1; i < 10; i++) {
    sum += bum1.getLineDigital(i);
  }
  if (service) Serial.println(sum);
  return sum;
}

float gyver() {
  r.input = digital_sensors();
  r.getResultTimer();
  return r.output;
}

int IRread() {
  int in = -1;
  while (Serial1.available()) {
    in = Serial1.read();
    if (in != -1 && in < 8) {
      ir = in;
    }
  }
  Serial.print("ir: ");
  Serial.println(ir);
  return ir;
}

void waitGreen() {
  while (IRread() != 2) {
    //    Serial.println("wait green");
    go(0, 10);
    servo_pos(0);
  }
  st = 0;
}

void wait_line() {
  st = 1;
  while (readlineRight() < 8) {
    go(20, 7);
    servo_pos(gyver());
    if (IRread() == 2) {
      st = 0;
      break;
    }
  }
  if (st == 1) {
    go(0, 10);
    waitGreen();
  }
}
