//SYSTEM_MODE(SEMI_AUTOMATIC);
//#include "Adafruit_MMA8451.h"
//#include "Adafruit_Sensor.h"

#define SOUND A1
#define BUZZER D2
#define ACCEL_X A2
#define ACCEL_Y A3
#define ACCEL_Z A4

#define READING_SOUND 0
#define READING_ACCEL_X 1
#define READING_ACCEL_Y 2
#define READING_ACCEL_Z 3
#define READING_LAT 4
#define READING_LNG 5
#define INTERVAL_MS 5000
#define INTERVAL_BUZZER 2000

//Adafruit_MMA8451 mma = Adafruit_MMA8451();

#define THRESHOLD_VALUE 50000
//400*32 //The threshold to turn on is 400.00*5/1024 = 1.95v
//value gotten from http://www.mouser.com/catalog/specsheets/Seeed_101020023.pdf
unsigned int lastUpdate = 0;
unsigned int buzzerUpdate = 0;
bool isBuzzerOn = false;


void setup(){
  Serial.begin(9600);
  //if (! mma.begin()) {
  //  Serial.println("Couldnt start");
  //  while (1);
  //}
  //Serial.println("MMA8451 found!");
  //mma.setRange(MMA8451_RANGE_2_G);
  pinMode(SOUND, INPUT);
  pinMode(BUZZER, OUTPUT);
}

void loop(){

  if (millis() - lastUpdate >= INTERVAL_MS){
    lastUpdate = millis();

    //clearing previous buzzer
    digitalWrite(BUZZER, LOW);

    //formatting data to send
    //the data is in the following formatting
    //[SOUND_READING, ACCEL_X, ACCEL_Y, ACCEL_Z, LAT, LNG]
    float data[6];

    //sound sensor
    long sum = 0;
    for (int i = 0; i < 32; i++){
      int sound = analogRead(SOUND);
      sum += sound;
    }
    data[READING_SOUND] = (float)sum;

    //accel readings
    //mma.read();
    //sensors_event_t event;
    //mma.getEvent(&event);
    //Serial.print(event.acceleration.x);
    //data[1] = event.acceleration.x;
    //data[2] = event.acceleration.y;
    //data[3] = event.acceleration.z;

    data[READING_ACCEL_X] = 1.23124124;
    data[READING_ACCEL_Y] = 0.421442142;
    data[READING_ACCEL_Z] = 0.41242341;


    //lat lng readings
    data[READING_LAT] = 37.428059;
    data[READING_LNG] = -122.174488;


    Particle.publish("push_data", String::format(
      "%f,%f,%f,%f,%f,%f", data[0],data[1],data[2],data[3],data[4],data[5]));

    // Buzzer
    Serial.println(sum);
    if (detectedPerson(sum)) {
      onBuzzer();
    }
  }

  if (isBuzzerOn && (millis() - buzzerUpdate >= INTERVAL_BUZZER)) {
    offBuzzer();
  }
}

bool detectedPerson(float sound) {
  if (sound >= THRESHOLD_VALUE) {
    return true;
  } else {
    return false;
  }
}

void onBuzzer() {
  Serial.println("buzz");
  digitalWrite(BUZZER, HIGH);
  isBuzzerOn = true;
  buzzerUpdate = millis();
}

void offBuzzer() {
  Serial.println("offbuzz");
  buzzerUpdate = millis();
  digitalWrite(BUZZER, LOW);
  isBuzzerOn = false;
}
