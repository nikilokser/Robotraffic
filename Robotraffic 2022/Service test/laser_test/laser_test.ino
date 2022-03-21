#include "Adafruit_VL53L0X.h"

Adafruit_VL53L0X lox = Adafruit_VL53L0X();

void setup() {
  Serial.begin(9600);
  if (!lox.begin()) {
    Serial.println(F("Failed to boot VL53L0X"));
    while(1);
  }
  else Serial.println(("Boot success VL53L0X"));
}

void loop() {
  VL53L0X_RangingMeasurementData_t measure;
  lox.rangingTest(&measure, false);
  if (measure.RangeStatus != 4 and measure.RangeMilliMeter/10 < 100) {
    Serial.print("Distance (cm): "); Serial.println(measure.RangeMilliMeter/10);
  } else {
    Serial.println(" out of range ");
  }
  delay(50);
}
