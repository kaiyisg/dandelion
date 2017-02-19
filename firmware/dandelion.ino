//SYSTEM_MODE(SEMI_AUTOMATIC);
#include "Adafruit_GPS.h"
#include "Adafruit_MMA8451.h"
#include "Adafruit_Sensor.h"
#include "math.h"

#define SOUND                 A0
#define BUZZER                D2

#define GPS_READ_INTERVAL_MS  1
#define READING_SOUND         0
#define READING_ACCEL_MAG     1
#define READING_LAT           2
#define READING_LON           3
#define ACCEL_INTERVAL_MS     2000
#define SOUND_INTERVAL_MS     1000
#define PUBLISH_INTERVAL_MS   3000
#define BUZZ_DURATION         2000
#define GPS_INTERVAL_MS       5000
#define SOUND_THRESHOLD_VALUE 55000

Adafruit_GPS gps = Adafruit_GPS();
Adafruit_MMA8451 mma = Adafruit_MMA8451();
Timer gps_read_timer(1, updateGPS);

unsigned long lastGPSUpdate = 0;
unsigned long lastSoundUpdate = 0;
unsigned long lastAccelUpdate = 0;
unsigned long lastPublish = 0;
unsigned long buzzerUpdate = 0;
long sum;
bool isBuzzerOn = false;
bool _gps_parse_failure;
bool fix;
double latitudeDegrees;
double longitudeDegrees;
double altitude;
float data[4];      //[SOUND_READING, ACCEL_MAG, LAT, LON]

void setup(){
  // Hardware pin setup
  Serial.begin(9600);
  pinMode(SOUND, INPUT);
  pinMode(BUZZER, OUTPUT);

  // Accelerometer setup
  Serial.println("Adafruit MMA8451 test!");
  if (!mma.begin()){
    Serial.println("Couldn't start");
    while (1);
  }
  Serial.println("MMA8451 found!");

  mma.setRange(MMA8451_RANGE_2_G);

  Serial.print("Range = "); Serial.print(2 << mma.getRange());
  Serial.println("G");

  // GPS setup
  gps.begin(9600);
  gps.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);
  delay(500);
  gps.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ);     // Default is 1 Hz update rate
  delay(500);
  gps.sendCommand(PGCMD_NOANTENNA);
  delay(500);
  gps_read_timer.start();     // Start the software timer
}

void loop(){
  // GPS reading + Particle Publish
  if ((millis() - lastGPSUpdate) >= GPS_INTERVAL_MS){
    lastGPSUpdate = millis();
    data[READING_LAT] = latitudeDegrees;
    data[READING_LON] = longitudeDegrees;
  }

  // Sound Sensor
  if ((millis() - lastSoundUpdate) >= SOUND_INTERVAL_MS){
    lastSoundUpdate = millis();
    sum = 0;
    for (int i=0; i<32; i++){
      int sound = analogRead(SOUND);
      sum += sound;
    }
    data[READING_SOUND] = (float)sum;
  }

  // Accelerometer
  if ((millis() - lastAccelUpdate) >= ACCEL_INTERVAL_MS){
    lastAccelUpdate = millis();
    mma.read();
    sensors_event_t event;
    mma.getEvent(&event);
    float accel = norm(event.acceleration.x, event.acceleration.y, event.acceleration.z);
    data[READING_ACCEL_MAG] = abs(accel-1);
  }

  if ((millis() - lastPublish) >= PUBLISH_INTERVAL_MS){
    lastPublish = millis();
    Particle.publish("push_data", String::format(
      "%f,%0.3f,%0.6f,%0.6f", data[0],data[1],data[2],data[3]));
  }

  // Buzzer On
  if (detectedPerson(sum, data[READING_ACCEL_MAG])
    && !isBuzzerOn
    && (millis() - buzzerUpdate >= BUZZ_DURATION)) {
      onBuzzer();
    }

  // Buzzer Off
  if (isBuzzerOn && (millis() - buzzerUpdate >= BUZZ_DURATION))
    offBuzzer();
}

bool detectedPerson(float sound, float accel){
  if (sound >= SOUND_THRESHOLD_VALUE || accel >= 0.05) {
    return true;
  } else {
    return false;
  }
}

void onBuzzer(){
  Serial.println("buzz");
  digitalWrite(BUZZER, HIGH);
  isBuzzerOn = true;
  buzzerUpdate = millis();
}

void offBuzzer(){
  Serial.println("offbuzz");
  buzzerUpdate = millis();
  digitalWrite(BUZZER, LOW);
  isBuzzerOn = false;
}

void updateGPS(){
  char c = gps.read();
  if (gps.newNMEAreceived()){
    if (!gps.parse(gps.lastNMEA())){
      _gps_parse_failure = true;
      return;
    }
    else{
      _gps_parse_failure = false;
      fix = gps.fix;
      latitudeDegrees = gps.latitudeDegrees;
      longitudeDegrees = gps.longitudeDegrees;
      altitude = gps.altitude;
    }
  }
}

float norm(float x, float y, float z){
  return sqrt(x*x + y*y + z*z);
}
