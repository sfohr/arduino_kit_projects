#include <Arduino.h>

const int sensorPin = A0;
const float baselineTemp = 24.0;
const float deltaTemp = 2.0;
const unsigned ledPins[] = {2, 3, 4, 5};
const int nTempLEDs = sizeof(ledPins) / sizeof(int);

float computeVoltage(int sensorVal);
float computeTempFromVolt(float voltage);

void updateTemperatureLEDs(float temperature, int nLEDs);

void setup() {
  Serial.begin(9600);

  for (int i = 0; i < nTempLEDs; i++) {
    pinMode(ledPins[i], OUTPUT);
    digitalWrite(ledPins[i], LOW);
  }
}

void loop() {
  int sensorVal = analogRead(sensorPin);
  Serial.print("Sensor: ");
  Serial.print(sensorVal);

  float voltage = computeVoltage(sensorVal);
  Serial.print(", Volt: ");
  Serial.print(voltage);

  float temperature = computeTempFromVolt(voltage);
  Serial.print(", Degree C: ");
  Serial.println(temperature);

  updateTemperatureLEDs(temperature, nTempLEDs);
  delay(1);
}

float computeVoltage(int sensor_value) {
  // ADC value (0 to 1024) to voltage (0.0 to 5.0V)
  return (sensor_value / 1024.0) * 5.0;
}

float computeTempFromVolt(float voltage) {
  // TMP36 scale factor: 10mV/°C
  return (voltage - .5) * 100.0;
}

void updateTemperatureLEDs(float temperature, int nLEDs) {
  int numLEDsOn = (temperature - baselineTemp) / deltaTemp;
  numLEDsOn = constrain(numLEDsOn, 0, nLEDs);

  for (int i = 0; i < nLEDs; i++) {
    if (i < numLEDsOn) {
      digitalWrite(ledPins[i], HIGH);
    } else {
      digitalWrite(ledPins[i], LOW);
    }
  }
}