int ir = 0;

int IRread(bool service = 0) {
  int in = -1;
  while (Serial1.available()) {
    in = Serial1.read();
    if (in != -1 && in < 8) {
      ir = in;
    }
  }
  if (service == 1) {
    Serial.print("ir: ");
    Serial.println(ir);
  }
  return ir;
}

void setup() {
  Serial1.begin(115200);
  Serial.begin(9600);
}

void loop() {
  IRread(1);
}
