#include <Wire.h>
#include <Adafruit_APDS9960.h>

// Gesture sensor object
Adafruit_APDS9960 gestureSensor = Adafruit_APDS9960();

// Pin definitions for White LEDs
const int ledRelaxationPin = 12; // Relaxation mood
const int ledNighttimePin = 14;   // Nighttime mood
const int ledRomanticPin = 12; // Romantic mood
const int ledFocusPin = 14;       // Focus/Work mood

void setup() {
  Serial.begin(9600);

  // Initialize the APDS9960 sensor
  if (!gestureSensor.begin()) {
    Serial.println("Error initializing APDS9960 sensor!");
    while (1);
  }
  Serial.println("APDS9960 sensor initialized.");

  // Enable gesture detection
  gestureSensor.enableGesture(true);

  // Initialize LED pins as output
  pinMode(ledRelaxationPin, OUTPUT);
  pinMode(ledNighttimePin, OUTPUT);
  pinMode(ledRomanticPin, OUTPUT);
  pinMode(ledFocusPin, OUTPUT);

  // Start with no LEDs on
  turnOffAllLEDs();
}

void loop() {
  // Check if a gesture is available
  if (gestureSensor.gestureValid()) {
    uint8_t gesture = gestureSensor.readGesture();
    switch (gesture) {
      case APDS9960_UP:
        Serial.println("Gesture: Up");
        turnOffAllLEDs(); // Turn off all LEDs
        digitalWrite(ledFocusPin, HIGH); // Turn on Focus LED
        break;
      case APDS9960_DOWN:
        Serial.println("Gesture: Down");
        turnOffAllLEDs(); // Turn off all LEDs
        digitalWrite(ledNighttimePin, HIGH); // Turn on Nighttime LED
        break;
      case APDS9960_LEFT:
        Serial.println("Gesture: Left");
        turnOffAllLEDs(); // Turn off all LEDs
        digitalWrite(ledRomanticPin, HIGH); // Turn on Romantic LED
        break;
      case APDS9960_RIGHT:
        Serial.println("Gesture: Right");
        turnOffAllLEDs(); // Turn off all LEDs
        digitalWrite(ledRelaxationPin, HIGH); // Turn on Relaxation LED
        break;
      default:
        Serial.println("No gesture detected");
        break;
    }
  }
}

// Function to turn off all LEDs
void turnOffAllLEDs() {
  digitalWrite(ledRelaxationPin, LOW);
  digitalWrite(ledNighttimePin, LOW);
  digitalWrite(ledRomanticPin, LOW);
  digitalWrite(ledFocusPin, LOW);
}
