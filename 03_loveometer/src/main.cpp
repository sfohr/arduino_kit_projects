#include <Arduino.h>

const int sensorPin = A0;                     // Analog input pin for temperature sensor
const float defaultBaselineTemp = 20.0;       // Default base temperature in °C
const float deltaTemp = 1.0;                  // Temperature difference for each LED to light up
const unsigned ledPinsTemp[] = {2, 3, 4, 5};  // LED pins to indicate temperature levels
const unsigned ledPinCalibrating = 8;         // LED pin to indicate calibration
const int nTempLEDs = sizeof(ledPinsTemp) / sizeof(int);

float baselineTemp = defaultBaselineTemp;     // Initial baseline temperature
int baselineTempSensorRaw = 0;                // Raw sensor value for baseline temperature

// Convert ADC value (0 to 1024) to voltage (0.0 to 5.0V)
float computeVoltage(int sensor_value) {
  return (sensor_value / 1024.0) * 5.0;
}

// Convert voltage to temperature in °C
float computeTempFromVolt(float voltage) {
  // TMP36 scale factor: 10mV/°C
  return (voltage - .5) * 100.0;
}

// Update the temperature indication LEDs
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

  // init LED pins
  for (int i = 0; i < nTempLEDs; i++) {
    pinMode(ledPinsTemp[i], OUTPUT);
    digitalWrite(ledPinsTemp[i], LOW);
  }
  pinMode(ledPinCalibrating, OUTPUT);
  digitalWrite(ledPinCalibrating, HIGH);

  // calibrate baseline temperature
  float baselineVoltageSum = 0.0;
  const int calibrationSamples = 100;
  for (int i = 0; i < calibrationSamples; i++) {
    int sensorVal = analogRead(sensorPin);
    baselineVoltageSum += computeVoltage(sensorVal);
    delay(10);
  }

  float baselineVoltage = baselineVoltageSum / calibrationSamples;
  baselineTemp = computeTempFromVolt(baselineVoltage);

  Serial.print("Baseline temperature (°C): ");
  Serial.println(baselineTemp);
  digitalWrite(ledPinCalibrating, LOW);
  delay(10);
}

void loop() {
  int sensorVal = analogRead(sensorPin);
  Serial.print("Sensor: ");
  Serial.print(sensorVal);

  float voltage = computeVoltage(sensorVal);
  Serial.print(", Volt: ");
  Serial.print(voltage);

  float temperature = computeTempFromVolt(voltage);
  Serial.print(", °C: ");
  Serial.println(temperature);

  updateTemperatureLEDs(temperature, baselineTemp, nTempLEDs);
  delay(10);
}
