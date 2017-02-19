// Example usage for Adafruit_MMA8451 library by ladyada.

#include "adafruit_MMA8451.h"

// Initialize objects from the lib
Adafruit_MMA8451 adafruit_MMA8451;

void setup() {
    // Call functions on initialized library objects that require hardware
    adafruit_MMA8451.begin();
}

void loop() {
    // Use the library's initialized objects and functions
    adafruit_MMA8451.process();
}
