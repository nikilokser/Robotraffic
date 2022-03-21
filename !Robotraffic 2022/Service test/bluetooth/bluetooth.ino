void setup() {
  Serial.begin(9600);         // включаем hardware-порт
  Serial3.begin(38400);  // включаем software-порт
}

void loop() {
    if (Serial3.available()) {
        char c = Serial3.read();  // читаем из software-порта
        Serial.print(c);                   // пишем в hardware-порт
    }
    if (Serial.available()) {
        char c = Serial.read();      // читаем из hardware-порта
        Serial3.write(c);            // пишем в software-порт
    }
}
