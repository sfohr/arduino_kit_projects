#include <Arduino.h>

const int greenLEDPin = 9;
const int redLEDPin = 11;
const int blueLEDPin = 10;

const int redSensorPin = A0;
const int greenSensorPin = A1;
const int blueSensorPin = A2;

int redValue = 0;
int greenValue = 0;
int blueValue = 0;

int redSensorValue = 0;
int greenSensorValue = 0;
int blueSensorValue = 0;

void setup() {
  Serial.begin(9600); 

  pinMode(greenLEDPin, OUTPUT);
  pinMode(redLEDPin, OUTPUT);
  pinMode(blueLEDPin, OUTPUT);
}

void loop() {
  redSensorValue = analogRead(redSensorPin);
  delay(5);

  greenSensorValue = analogRead(greenSensorPin);
  delay(5);

  blueSensorValue = analogRead(blueSensorPin);
  delay(5);

  Serial.println("Raw data from sensor:");
  Serial.print("\t red: ");
  Serial.print(redSensorValue);
  Serial.print("\t green: ");
  Serial.print(greenSensorValue);
  Serial.print("\t blue: ");
  Serial.println(blueSensorValue);

  // Raw sensor values range from 0 to 1023, convert to RGB, 0 to 255
  redValue = redSensorValue/4;
  greenValue = blueSensorValue/4;
  blueValue = blueSensorValue/4;

  Serial.println("Summary of sensor values:");
  Serial.print("\t red: ");
  Serial.print(redValue);
  Serial.print("\t green: ");
  Serial.print(greenValue);
  Serial.print("\t blue: ");
  Serial.println(blueValue);

  // Digital pins output binary signals (0/1). To control LED brightness, we use Pulse Width
  // Modulation (PWM), which adjusts the ratio of time the signal is 1 versus 0. This creates
  // a perceived analog output, dimming the LEDs based on the duty cycle (percentage of time 
  // the signal stays high during each cycle)
  analogWrite(redLEDPin, redValue);
  analogWrite(greenLEDPin, greenValue);
  analogWrite(blueLEDPin, blueValue);
  delay(1000);
}