//SYSTEM_MODE(SEMI_AUTOMATIC);

#define PIEZO  A0
#define SOUND  A1
#define BUZZER D2
#define ACCEL_X A2
#define ACCEL_Y A3
#define ACCEL_Z A4

#include "lib/Adafruit_MMA8451.h"
#include "lib/Adafruit_Sensor.h"

//#include <Adafruit_MMA8451.h>
//#include <Adafruit_Sensor.h>
Adafruit_MMA8451 mma = Adafruit_MMA8451();

// Piezo Sensor
//int piezoValue = analogRead(PIEZO);
//Serial.println(piezoValue);
//Serial.println("");

#define THRESHOLD_VALUE 400*32 //The threshold to turn on is 400.00*5/1024 = 1.95v
//value gotten from http://www.mouser.com/catalog/specsheets/Seeed_101020023.pdf

void setup(){
  Serial.begin(9600);
  if (! mma.begin()) {
    Serial.println("Couldnt start");
    while (1);
  }
  Serial.println("MMA8451 found!");
  mma.setRange(MMA8451_RANGE_2_G);
  pinMode(PIEZO, OUTPUT);
  pinMode(SOUND, INPUT);
  pinMode(BUZZER, OUTPUT);
}

void loop(){
  //clearing previous buzzer
  digitalWrite(BUZZER, LOW);

  //formatting data to send
  float data[6];
  //[SOUND_READING, ACCEL_X, ACCEL_Y, ACCEL_Z, LAT, LNG]

  //sound sensor
  Serial.println("Sound:");
  long sum = 0;
  for (int i = 0; i < 32; i++){
    int sound = analogRead(SOUND);
    Serial.println(sound);
    sum += sound;
  }
  data[0] = (float)sum;

  //accel readings
  mma.read();
  sensors_event_t event;
  mma.getEvent(&event);
  //Serial.print(event.acceleration.x);
  data[1] = event.acceleration.x;
  data[2] = event.acceleration.y;
  data[3] = event.acceleration.z;

  //lat lng readings
  data[4] = 37.428059;
  data[5] = -122.174488;


  Particle.publish("push_data", String::format(
    "%f,%f,%f,%f,%f,%f", data[0],data[1],data[2],data[3],data[4],data[5]));

  // Buzzer
  if (sum >= THRESHOLD_VALUE) {
    digitalWrite(BUZZER, HIGH);
    delay(1000);
    digitalWrite(BUZZER, LOW);
  }
  //delay(1000);

  Serial.println("done");
  delay(1000);
}
