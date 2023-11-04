#include <Arduino.h>
#include <Ticker.h>

#define ledPin D2
#define signalPin D4

Ticker signalTicker;

const int desiredFrequency = 50; // Desired frequency in 50Hz
float interval; // Interval between signal toggles in microseconds

void toggleSignal() {
  static bool toggle = false; // Static variable to remember the state of the signal
  digitalWrite(signalPin, toggle = !toggle); 
}

void setup() {
  Serial.begin(115200); 
  pinMode(signalPin, OUTPUT); 
  pinMode(ledPin, OUTPUT); 

  interval = 1.0 / desiredFrequency * 1000000; // Calculate interval based on desired frequency
  signalTicker.attach(interval / 1000000, toggleSignal); // Attach toggleSignal function to Ticker
}

void loop() {
  digitalWrite(ledPin, HIGH); 
  Serial.println("LED status: " + String(digitalRead(ledPin)));
  delay(2000);
  digitalWrite(ledPin, LOW);
  Serial.println("LED status: " + String(digitalRead(ledPin)));
  delay(2000);
}
