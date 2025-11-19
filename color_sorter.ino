#include <Servo.h>
#include <Arduino.h>
#include <mwc_stepper.h>

int command = 0;

#define EN 3
#define DIR 8
#define STEP 5
const int ms1Pin = 10;
const int ms2Pin = 11;
const int ms3Pin = 12;

#define EN_PIN A1
#define DIR_PIN 13
#define STEP_PIN 2
const int ms1 = 4;
const int ms2 = 6;
const int ms3 = 7;

Servo myservo;

#define RPM 40
#define RPM2 20
#define PULSE 1800

#define ClOCKWISE 1
#define OTHERWISE 0

MWCSTEPPER nema23(EN_PIN, DIR_PIN, STEP_PIN);
MWCSTEPPER nema(EN, DIR, STEP);

void turn(int val, int r) {
  nema23.set(r, RPM, PULSE);
  for (size_t i = 0; i < val; i++) {
    nema23.run();
  }
}

void turn2(int val, int r) {
  nema.set(r, RPM2, PULSE);
  for (size_t i = 0; i < val; i++) {
    nema.run();
  }
}

void mov1() {
  delay(3000);
  turn(150, 0); // DROP
  delay(800);
  myservo.write(140);
  delay(700);
  turn(150, 1);
  delay(700);
  turn2(400, 0); // cw
  delay(700);
  turn(100, 0);
  delay(1000);
  myservo.write(160);
  delay(700);
  turn(100, 1);
  delay(1000);
  turn2(400, 1);
  delay(1000);
  delay(1000);
}

void mov2() {
  delay(3000);
  turn(150, 0);
  delay(1000); // drop
  myservo.write(140);
  delay(700);
  turn(150, 1);
  delay(700);
  turn2(800, 0); // cw
  delay(700);
  turn(50, 0);
  delay(700);
  myservo.write(160);
  delay(700);
  turn(50, 1);
  delay(1000);
  turn2(800, 1);
  delay(1000);
  delay(1000);
}

void setup() {
  myservo.write(135);
  delay(3000);
  Serial.begin(1000000);

  pinMode(ms1Pin, OUTPUT);
  pinMode(ms2Pin, OUTPUT);
  pinMode(ms3Pin, OUTPUT);
  pinMode(ms1, OUTPUT);
  pinMode(ms2, OUTPUT);
  pinMode(ms3, OUTPUT);
  myservo.attach(A0); // attaches the servo on pin 9 to the servo object

  nema23.init();
  nema.init();

  // Set microstepping mode (e.g., 1/16 step)
  digitalWrite(ms1Pin, HIGH);
  digitalWrite(ms2Pin, HIGH);
  digitalWrite(ms3Pin, HIGH);
  digitalWrite(ms1, HIGH);
  digitalWrite(ms2, HIGH);
  digitalWrite(ms3, HIGH);
  
  turn(150, 1);
  myservo.write(170);
  delay(5000);
}

void loop() {
  if (Serial.available() > 0) {
    String data = Serial.readStringUntil('\n');
    data.trim(); // Remove any leading/trailing whitespace

    if(data == "Red") {
      command = 1;
    } else if(data == "Green") {
      command = 2;
    } else if("White") {
      command = 0;
    }
  //delay(10000);
    // Clear the data variable
    data = "";
  }
else
//command=0;


  if (command == 1) {
    mov1();
    command = 1; // Reset command
  } else if (command == 2) {
    mov2();
    //command = 0; // Reset command
  }
}
