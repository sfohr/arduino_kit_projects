#include <Arduino.h>

int switchState = 0;

void setup() {
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(2, INPUT);

  for(int i = 0; i<25; i++){
    digitalWrite(4, HIGH);
    digitalWrite(5, HIGH);
    delay(100);
    digitalWrite(4, LOW);
    digitalWrite(5, LOW);
    delay(100);
  }
}

void loop() {
  switchState = digitalRead(2);
  if (switchState == LOW) {   // button not pressed
    delay(20);
    digitalWrite(3, HIGH);    // green
    digitalWrite(4, LOW);     // red
    digitalWrite(5, LOW);     // red
  }
  else {                      // button pressed
    digitalWrite(3, LOW);
    digitalWrite(4, LOW);
    digitalWrite(5, HIGH);
    delay(200);

    digitalWrite(4, HIGH);
    digitalWrite(5, LOW);
    delay(200);
  }
}
