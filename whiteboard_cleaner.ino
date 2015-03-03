#include "IRremote.h"

IRsend irsend(D5);

int dirpin1           = D0;
int steppin1          = D1;
int buttonPin1        = A4;
int buttonState1      = 0;
float position1       = 0;
bool shouldCalibrate1 = false;

int dirpin2           = D2;
int steppin2          = D3;
int buttonPin2        = A3;
int buttonState2      = 0;
float position2       = 0;
bool shouldCalibrate2 = false;

int ledPin = D7;

void setup()
{
  pinMode(dirpin1,    OUTPUT);
  pinMode(steppin1,   OUTPUT);
  pinMode(buttonPin1, INPUT);

  pinMode(dirpin2,    OUTPUT);
  pinMode(steppin2,   OUTPUT);
  pinMode(buttonPin2, INPUT);

  pinMode(ledPin, OUTPUT);

  Spark.function("moveTo1", moveTo1);
  Spark.function("moveTo2", moveTo2);
  Spark.function("calibrate", calibrate);
  Spark.function("irSend", irSend);
}

void loop()
{
  if (shouldCalibrate1 == true) {
    digitalWrite(ledPin, HIGH);
    performCalibration1();
  } else if (shouldCalibrate2 == true) {
    digitalWrite(ledPin, HIGH);
    performCalibration2();
  }
  else {
    digitalWrite(ledPin, LOW);
  }
}

int calibrate(String input) {
  if (input == "1in") {
    shouldCalibrate1 = true;
    digitalWrite(dirpin1, HIGH);
  } else if (input == "1out") {
    shouldCalibrate1 = true;
    digitalWrite(dirpin1, LOW);
  } else if (input == "2in") {
    shouldCalibrate2 = true;
    digitalWrite(dirpin2, HIGH);
  } else if (input == "2out") {
    shouldCalibrate2 = true;
    digitalWrite(dirpin2, LOW);
  }

  return 1;
}

void performCalibration1() {
  buttonState1 = digitalRead(buttonPin1);

  movement1(20); // 80 steps for 1 revolution

  if (buttonState1 == HIGH) {
    shouldCalibrate1 = false;
    position1 = 0;
  }
}

void performCalibration2() {
  buttonState2 = digitalRead(buttonPin2);

  movement2(20); // 80 steps for 1 revolution

  if (buttonState2 == HIGH) {
    shouldCalibrate2 = false;
    position2 = 0;
  }
}

// 1 revolution is 1 position1
int moveTo1(String value) {
  char * valueChar = new char[value.length() + 1];
  strcpy(valueChar, value.c_str());

  float newPosition = atof(valueChar);

  if(newPosition > position1) {
    digitalWrite(dirpin1, LOW);
    movement1((newPosition - position1) * 1600);
  } else {
    digitalWrite(dirpin1, HIGH);
    movement1((position1 - newPosition) * 1600);
  }

  position1 = newPosition;

  return 1;
}

// 1 revolution is 1 position1
int moveTo2(String value) {
  char * valueChar = new char[value.length() + 1];
  strcpy(valueChar, value.c_str());

  float newPosition = atof(valueChar);

  if(newPosition > position2) {
    digitalWrite(dirpin2, LOW);
    movement2((newPosition - position2) * 1600);
  } else {
    digitalWrite(dirpin2, HIGH);
    movement2((position2 - newPosition) * 1600);
  }

  position2 = newPosition;

  return 1;
}

void movement1(int steps) {
  for (int i = 0; i < steps; i++) {
    digitalWrite(steppin1, LOW);
    digitalWrite(steppin1, HIGH);
    delayMicroseconds(500);
  }
}

void movement2(int steps) {
  for (int i = 0; i < steps; i++) {
    digitalWrite(steppin2, LOW);
    digitalWrite(steppin2, HIGH);
    delayMicroseconds(500);
  }
}

int irSend(String value) {
  char * valueChar = new char[value.length() + 1];
  strcpy(valueChar, value.c_str());
  int toSend = atof(valueChar);

  irsend.sendSony(toSend, 12);
  return 1;
}
