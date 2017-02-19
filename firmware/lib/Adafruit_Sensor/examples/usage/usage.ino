// Example usage for Adafruit_Sensor library by ladyada.

#include "adafruit_Sensor.h"

// Initialize objects from the lib
Adafruit_Sensor adafruit_Sensor;

void setup() {
    // Call functions on initialized library objects that require hardware
    adafruit_Sensor.begin();
}

void loop() {
    // Use the library's initialized objects and functions
    adafruit_Sensor.process();
}
