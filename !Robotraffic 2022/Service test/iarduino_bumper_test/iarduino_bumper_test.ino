#include <Wire.h>
#include <iarduino_I2C_Bumper.h>
#include "buzzer.h"

#define calibrat 1
#define digit 1

iarduino_I2C_Bumper bum(0x09);
iarduino_I2C_Bumper bum1(0x08);
bool f, g;

void setup() {
  Serial.begin(115200);
  buz_begin();
  bum.begin();
  bum1.begin();
  if (calibrat) {
    beep();
    delay(2500);
    f = bum.setCalibrationRun();
    if (f) {
      Serial.println("Линия 1 считана!");
      success();
    }
    else {
      Serial.println("Ошибка!.");
      fail();
      while (1) {}
    }
    delay(1000);
    beep();
    g = bum1.setCalibrationRun();
    if (g) {
      Serial.println("Линия 2 считана!");
      success();
    }
    else {
      Serial.println("Ошибка!.");
      fail();
      while (1) {}
    }
    delay(1000);
    beep();
    delay(2500);
    f = bum.setCalibrationEnd();
    if (f) {
      Serial.println("Фон 1 считан!");
      success();
    }
    else {
      Serial.println("Ошибка!.");
      fail();
      while (1) {}
    }
    g = bum1.setCalibrationEnd();
    if (g) {
      Serial.println("Фон 2 считан!");
      success();
    }
    else {
      Serial.println("Ошибка!.");
      fail();
      while (1) {}
    }
    delay(250);
    mega_success();
  }
}

void loop() {
  unsigned long sum = 0;
  for (uint8_t i = 1; i < 10; i++) {
    if (digit) Serial.print(bum.getLineDigital(i));
    else Serial.print(bum.getLineAnalog(i));
    Serial.print("\t");
    sum += bum.getLineAnalog(i);
  }
  for (uint8_t i = 1; i < 10; i++) {
    if (digit) Serial.print(bum1.getLineDigital(i));
    else Serial.print(bum1.getLineAnalog(i));
    Serial.print("\t");
    sum += bum1.getLineAnalog(i);
  }
  Serial.println(sum);
  delay(100);
}
