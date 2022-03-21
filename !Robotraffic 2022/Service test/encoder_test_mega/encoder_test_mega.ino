void setup() {
  Serial2.begin(115200);
  Serial.begin(9600);
  Serial3.begin(38400);
}

int se = 0;
int encoder = 0;

void encoder_check() {
  if (Serial2.available()) {
    se = Serial2.parseInt();
    if (se != 0) {
      encoder = se;
    }
  }
  Serial.print("encoder: ");
  Serial.println(encoder);
  Serial3.println(byte(encoder));
}

void loop() {
  encoder_check();
}
