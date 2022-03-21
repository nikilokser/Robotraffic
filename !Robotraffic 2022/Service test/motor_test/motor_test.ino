#include <Servo.h>

Servo ESC;

unsigned long timing = 0;
int throttle = -10;
int act_speed = 0;
int sspeed = 0;
int se;
int encoder = 0;
int s = 0;


void encoder_check(bool service = 0) {
  if (Serial2.available()) {
    se = Serial2.parseInt();
    if (se != 0) {
      encoder = se;
    }
  }
  if (service) {
    Serial.print("encoder: ");
    Serial.println(encoder);
  }
}

void go(int need_speed, int intensivity) {
  if (need_speed < 0) {
    ESC.writeMicroseconds(1000);
  }
  else {
    if (act_speed < need_speed) {
      if (millis() - timing > map(intensivity, 1, 10, 250, 20)) {
        act_speed = s;
        s += 2;
        timing = millis();
      }
    }
    else if (act_speed > need_speed) {
      if (millis() - timing > map(intensivity, 1, 10, 250, 10)) {
        act_speed = s;
        s -= 2;
        timing = millis();
      }
    }
    ESC.writeMicroseconds(map(constrain(s, -100, 100), -100, 100, 1000, 2000));
  }
}

void setup() {
  ESC.attach(45);
  Serial.begin(115200);
  Serial2.begin(115200);
}

void loop() {
  go(0, 1);
}
