#include "func.h"

void setup() {
  r.Kp = 0.275;
  r.Ki = 0.05;
  r.Kd = 0.00025;
  set();
  waitGreen();
}

void loop() {
  encoder_check();
  sspeed = 49;

  if (encoder > 57) {
    r.integral = 0;
    vpered = 0;
    vpravo = 1;
    r.Kp = 1.35;
    r.Ki = 0.00005;
    r.Kd = 0.0065;
  }

  if (encoder > 144) {
    vpered = 1;
    vpravo = 0;
    r.integral = 0;
    r.Kp = 0.6;
    r.Ki = 0.000000015;
    r.Kd = 0.0000325;
  }

  if (encoder > 186) {
    r.integral = 0;
    r.Kp = 1.35;
    r.Ki = 0.00000015;
    r.Kd = 0.003;
    vpered = 0;
    vlevo = 1;
  }
  if (encoder > 255) {
    sspeed = 100;
    intens = 7;
  }
  if (encoder > 260) {
    r.integral = 0;
    vlevo = 0;
    vpered = 1;
    r.Kp = 0.45;
    r.Ki = 0.05;
    r.Kd = 0.0025;
  }
  if (encoder > 325) {
    sspeed = 0;
  }


  if (readline() < 1) {
    while (true) {
      go(0, 10);
      if (act_speed == 0 and st == 0) {
        if (encoder > 325) mega_success();
        else fail();
        st = 1;
      }
    }
  }
  go(sspeed, intens);
  servo_pos(gyver());
}
