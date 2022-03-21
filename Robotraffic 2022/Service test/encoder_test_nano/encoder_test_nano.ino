int encoder = 0;
int old = 0;
#define enc 3

void encoder_plus() {
  encoder++;
}

void setup() {
  Serial.begin(115200);
  attachInterrupt(1, encoder_plus, RISING);
}

void loop() {
  if (encoder != old) {
    Serial.println(encoder);
    old = encoder;
  }
  if (Serial.available() > 0) {
    encoder = 0;
  }
}
