#include <Arduino.h>

const int sensorPin = A0;
float baselineTemp = 20.0;
const float deltaTemp = 2.0;
const unsigned ledPinsTemp[] = {2, 3, 4, 5};
const unsigned ledPinCalibrating = 8;
const int nTempLEDs = sizeof(ledPinsTemp) / sizeof(int);
int baselineTempSensorRaw = 0;

float computeVoltage(int sensor_value) {
  // ADC value (0 to 1024) to voltage (0.0 to 5.0V)
  return (sensor_value / 1024.0) * 5.0;
}

float computeTempFromVolt(float voltage) {
  // TMP36 scale factor: 10mV/°C
  return (voltage - .5) * 100.0;
}

void updateTemperatureLEDs(float temperature, float baseline_temp, int nLEDs) {
  int numLEDsOn = (temperature - baseline_temp) / deltaTemp;
  numLEDsOn = constrain(numLEDsOn, 0, nLEDs);

  for (int i = 0; i < nLEDs; i++) {
    if (i < numLEDsOn) {
      digitalWrite(ledPinsTemp[i], HIGH);
    } else {
      digitalWrite(ledPinsTemp[i], LOW);
    }
  }
}

void setup() {
  Serial.begin(9600);

  for (int i = 0; i < nTempLEDs; i++) {
    pinMode(ledPinsTemp[i], OUTPUT);
    digitalWrite(ledPinsTemp[i], LOW);
  }
  pinMode(ledPinCalibrating, OUTPUT);
  digitalWrite(ledPinCalibrating, HIGH);
  int i = 0;
  float baselineVoltageSum = 0.0;
  int sensorVal = 0;
  while (millis() < 1000) {
    sensorVal = analogRead(sensorPin);
    baselineVoltageSum += computeVoltage(sensorVal);
    i += 1;
    delay(1);
  }
  float baselineVoltage = baselineVoltageSum / i;
  baselineTemp = computeTempFromVolt(baselineVoltage);
  Serial.print("Baseline temperatur (degree celsius): ");
  Serial.println(baselineTemp);
  digitalWrite(ledPinCalibrating, LOW);
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

  updateTemperatureLEDs(temperature, baselineTemp, nTempLEDs);
  delay(1);
}
