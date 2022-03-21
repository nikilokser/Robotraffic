#include <Wire.h>
#include <iarduino_I2C_Bumper.h>
#include <Servo.h>
#include "GyverPID.h"
#include "buzzer.h"

iarduino_I2C_Bumper bum(0x09);
iarduino_I2C_Bumper bum1(0x08);
Servo servo;
Servo ESC;
GyverPID r(0.1, 0.01, 0.01, 20);

int s = 0;
int deg = 0;
int ir = 0;
int out = 0;
bool st = 0;
int dd;

void servo_pos(int degres) {
  degres = constrain(degres, -100, 100);
  degres = map(degres, -100, 100, 65, 115);
  servo.write(degres);
}

void set() {
  Serial.begin(9600);
  Serial1.begin(115200);
  Serial2.begin(115200);
  Serial3.begin(38400);
  Wire.begin();

  bum.begin();
  bum1.begin();

  buz_begin();

  servo.attach(44);
  ESC.attach(45);

  r.setDirection(REVERSE);
  r.setLimits(-100, 100);
  r.setpoint = 0;
}

void go(int pwm) {
    ESC.writeMicroseconds(map(pwm, -100, 100, 1100, 1900));
}

float digital_sensors() {
  float a = bum.getErrPID();
  float b = bum1.getErrPID();
  out = map(a+b, -10, 10, -100, 100);
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
    go(0);
    servo_pos(0);
  }
  st = 0;
}

void wait_line() {
  st = 1;
  while (readline() < 11) {
    go(18);
    servo_pos(gyver());
    if (IRread() == 2) {
      st = 0;
      break;
    }
  }
  if (st == 1) {
    go(-40);
    delay(100);
    beep();
    waitGreen();
  }
}
