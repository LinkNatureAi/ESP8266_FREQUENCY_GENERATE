#include <Arduino.h>
#include <Ticker.h>

Ticker blinker;

// Define pin constants
const int ledPin = D2;
const int signalPin = D4;

// Define signal parameters
const int frequency = 5;                          // Frequency in 5Hz
const unsigned long period = 1000000 / frequency; // Period in microseconds

volatile bool signalState = LOW; // Initialize signal state

// Function to generate low-frequency signal
void ICACHE_RAM_ATTR onTimerISR()
{
  signalState = !signalState;           // Toggle signal state
  digitalWrite(signalPin, signalState); // Set pin state
  timer1_write(period);
}

void setup()
{
  // Initialize serial communication
  Serial.begin(115200);

  // Initialize pin modes
  pinMode(ledPin, OUTPUT);
  pinMode(signalPin, OUTPUT);
  digitalWrite(signalPin, LOW); // Ensure the signal pin is initially LOW

  // Set up the timer interrupt for generating low-frequency signal
  timer1_attachInterrupt(onTimerISR);
  timer1_enable(TIM_DIV16, TIM_EDGE, TIM_SINGLE); // Use a lower timer division for a lower frequency
  timer1_write(period);
}

void loop()
{
  // Blink the LED every 1 second
  digitalWrite(ledPin, HIGH);
  Serial.println("LED status: " + String(digitalRead(ledPin)));
  delay(1000);
  digitalWrite(ledPin, LOW);
  Serial.println("LED status: " + String(digitalRead(ledPin)));
  delay(1000);
}
