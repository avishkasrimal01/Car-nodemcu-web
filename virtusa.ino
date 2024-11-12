
#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#define trig 13 //d7
#define echo 15 //d8
#define buzzer 12//d6

#define FIREBASE_HOST "virtusa-project-3f73a-default-rtdb.firebaseio.com" 
#define FIREBASE_AUTH "FPUv0VWDVjz0GHNA2OUZn5sizjSlBniYQe5qjqvD"

#define WIFI_SSID "Home_Wifi" 
#define WIFI_PASSWORD "bdg92813" 

long t, cm;

void setup() {

  Serial.begin(9600);

  pinMode(echo, INPUT);
  pinMode(trig, OUTPUT);
  pinMode(buzzer, OUTPUT);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD); 
  Serial.print("connecting"); 
  while (WiFi.status() != WL_CONNECTED) { 
    Serial.print("."); 
    delay(500); 
  } 
  Serial.println(); 
  Serial.print("connected: "); 
  Serial.println(WiFi.localIP()); 
   
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH); 

}

void loop() {
  DistanceCal();

  if(cm < 5){
    Buzzer();
  }else{
    BuzzerOff();
  }

}


void DistanceCal() {

  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);


  t = pulseIn(echo, HIGH);
  cm = t / 29 / 2 ;

  Serial.print("Sonic: ");
  Serial.print(cm);
  Serial.println("cm");

  Firebase.setFloat("Virtusa/SensorValues/cm", cm);
  delay(10);

}


void Buzzer() {

  digitalWrite(buzzer, HIGH);
  delay(100);
  digitalWrite(buzzer, LOW);
  delay(100);
}

void BuzzerOff() {

  digitalWrite(buzzer, LOW);
}
