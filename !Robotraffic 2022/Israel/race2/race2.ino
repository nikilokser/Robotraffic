#include "func.h"

void setup() {
  r.Kp = 0.5;
  r.Ki = 0.05;
  r.Kd = 0;
  set();
  waitGreen();
}

void loop() {
  encoder_check();
  sspeed = 49;
  //первыйй поворот
  if (encoder > 57) {
    r.integral = 0;
    sspeed = 47;
    intens = 4;
    vpered = 0;
    vpravo = 1;
    r.Kp = 2.475; //2,45
    r.Ki = 0.015;
    r.Kd = 2.5; //25
  }

  if (encoder > 146) {   //2 прямая
    r.integral = 0;
    vpered = 1;
    vpravo = 0;
    //r.Kp = 0.85;   //0.025                   0,5 тоже хорошо
    //r.Kd = 20;   //1.6                      1,6 тоже хорошо
    r.Kp = 0.5;
    r.Ki = 0;
    r.Kd = 8; //7,5
  }

  if (encoder > 152) {
    sspeed = 45;
    intens = 7;
  }

  if (encoder > 186) {
    r.integral = 0;
    r.Ki = 0.0075;
    r.Kp = 2.6;  //1.8      второй поворот
    r.Kd = 2.5; //20
    vpered = 0;
    vlevo = 1;
  }
  if (encoder > 257) {
    r.integral = 0;
    sspeed = 90;
    intens = 6;
    vlevo = 0;
    vpered = 1;
    r.Kp = 0.4;
    r.Ki = r.Kp * 0.2;
    r.Kd = r.Kp * 1.1;
  }
  if (encoder > 330) {
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
