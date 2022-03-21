#include <Octoliner.h>

Octoliner octoliner(45);

void setup() {
  Serial.begin(115200);
  octoliner.begin();
  delay(1000);
  octoliner.changeAddr(42);
  octoliner.saveAddr();
  Serial.print("done");
}

void loop() {
  // put your main code here, to run repeatedly:

}
