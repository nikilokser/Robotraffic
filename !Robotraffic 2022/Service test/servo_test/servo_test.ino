#include <Servo.h>

Servo servo;
int pos = 65;
int i = 1;


void setup() {
  servo.attach(44);
}

void loop() {
  while (1) {
    pos = pos + i;
    servo.write(pos);
    delay(20);
    if (pos >= 115) i = -1;
    if (pos <= 65) i = 1;
  }
}
