#include <Arduino.h>

const int sensorPin = A0;
const float baselineTemp = 26.0;

void setup() {
  Serial.begin(9600);

  for (int pinNumber = 2; pinNumber < 5; pinNumber++) {
    pinMode(pinNumber, OUTPUT);
    digitalWrite(pinNumber, LOW);
  }
}

void loop() {
  int sensorVal = analogRead(sensorPin);
  Serial.print("Sensor: ");
  Serial.print(sensorVal);

  // ADC value (0 to 1024) to voltage (0.0 to 5.0V)
  float voltage = (sensorVal / 1024.0) * 5.0;
  Serial.print(", Volt: ");
  Serial.print(voltage);
  Serial.print(", Degree C: ");

  // TMP36 has an output scale factor of 10 mV/°C, 10 mV change indicates 1°C change
  float temperature = (voltage - .5) *  100.0;
  Serial.println(temperature);

  if (temperature < baselineTemp + 2.0){
    digitalWrite(2, LOW);
    digitalWrite(3, LOW);
    digitalWrite(4, LOW);
  } else if (temperature  >= baselineTemp + 2.0 && temperature < baselineTemp + 4.0) {
    digitalWrite(2, HIGH);
    digitalWrite(3, LOW);
    digitalWrite(4, LOW);
  } else if (temperature >= baselineTemp + 4.0 && temperature < baselineTemp + 6.0) {
    digitalWrite(2, HIGH);
    digitalWrite(3, HIGH);
    digitalWrite(4, LOW);
  } else if (temperature >= baselineTemp + 6.0) {
    digitalWrite(2, HIGH);
    digitalWrite(3, HIGH);
    digitalWrite(4, HIGH);
  }
  delay(1);
}
