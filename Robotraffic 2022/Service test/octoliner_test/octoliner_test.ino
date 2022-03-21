#include <Octoliner.h>

Octoliner octoliner(42);
Octoliner octoliner1(45);

void setup() {
  Serial.begin(115200);
  octoliner.begin();
  octoliner1.begin();
  delay(1000);
  octoliner.optimizeSensitivityOnBlack();
  Serial.print("octoliner ok, sensitivity: "); Serial.println(octoliner.getSensitivity());
  octoliner1.optimizeSensitivityOnBlack();
  Serial.print("octoliner2 ok, sensitivity: "); Serial.println(octoliner1.getSensitivity());
}

void loop() {
  int sum = 0;
  for (uint8_t i = 0; i < 8; i++) {
    Serial.print(octoliner.analogRead(i));
    Serial.print("\t");
    sum += octoliner.analogRead(i);
  }
  for (uint8_t i = 0; i < 8; i++) {
    Serial.print(octoliner1.analogRead(i));
    Serial.print("\t");
    sum += octoliner1.analogRead(i);
  }
  Serial.println(sum);
  delay(100);
}
