//SYSTEM_MODE(SEMI_AUTOMATIC);

#define PIEZO  A0
#define SOUND  A1
#define BUZZER D2

void setup(){
  Serial.begin(9600);
  pinMode(PIEZO, OUTPUT);
  pinMode(SOUND, INPUT);
  pinMode(BUZZER, OUTPUT);
}

void loop(){
  //Particle.publish("push_vibration");

  // Piezo Sensor
  int piezoValue = analogRead(PIEZO);
  Serial.println(piezoValue);
  Serial.println("");
  delay(1000);

  // Sound Sensor
  Serial.println("Sound:");
  long sum = 0;
  for (int i=0; i❤2; i++){
    int sound = analogRead(SOUND);
    Serial.println(sound);
    sum += sound;
  }
  Serial.println("");
  Serial.print("Sum = ");
  Serial.println(sum);
  Serial.println("");
  String sumstring = String(sum);
  Particle.publish("sound_sum", sumstring);

  // Buzzer
  digitalWrite(BUZZER, HIGH);
  delay(1000);
  digitalWrite(BUZZER, LOW);
  delay(1000);

  Serial.println("done");
  delay(1000);
}
