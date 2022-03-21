#define buz 2

void buz_begin() {
  pinMode(buz, OUTPUT);
}

void success() {
  tone(buz, 500);
  delay(100);
  noTone(buz);
  delay(100);
  tone(buz, 700);
  delay(100);
  noTone(buz);
  delay(100);
  tone(buz, 900);
  delay(100);
  noTone(buz);
}

void mega_success() {
  tone(buz, 500);
  delay(100);
  noTone(buz);
  delay(100);
  tone(buz, 600);
  delay(100);
  noTone(buz);
  delay(100);
  tone(buz, 700);
  delay(100);
  noTone(buz);
  delay(100);
  tone(buz, 800);
  delay(100);
  noTone(buz);
  delay(100);
  tone(buz, 900);
  delay(100);
  noTone(buz);
  delay(100);
  tone(buz, 1000);
  delay(150);
  noTone(buz);
  delay(300);
  tone(buz, 1050);
  delay(150);
  noTone(buz);
  delay(100);
  tone(buz, 1050);
  delay(150);
  noTone(buz);
  delay(100);
  tone(buz, 1050);
  delay(200);
  noTone(buz);
}

void fail() {
  tone(buz, 500);
  delay(300);
  noTone(buz);
  delay(100);
  tone(buz, 300);
  delay(300);
  noTone(buz);
  delay(100);
  tone(buz, 100);
  delay(500);
  noTone(buz);
}

void beep() {
  tone(buz, 700);
  delay(100);
  noTone(buz);
}
