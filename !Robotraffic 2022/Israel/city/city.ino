#include "func.h"

void setup() {
  r.Kp = 1.375; //s = 30 p = 1.35 i = 0.05 d = 0.0015
  r.Ki = 0.05; //s = 35 p = 1.35 i = 0.05 d = 0.0015 not working
  r.Kd = 0.0015;
  set();
  beep();
  waitGreen();
}

void loop() {
  ir = IRread();
  go(s);
  servo_pos(gyver());

  if (ir != 2 && ir != 3) {
    wait_line();
  }
  else {
    s = 29;
  }

  if (readline() < 1) {
    while (true) {
      go(0);
      if (st == 0) {
        fail();
        st = 1;
      }
    }
  }
  if (readline() > 13) r.integral = 0;
}
