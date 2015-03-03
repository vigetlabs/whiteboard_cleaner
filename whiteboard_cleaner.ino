#include "IRremote.h"
#include "Stepper.h"

IRsend irsend(D5);

Stepper stepper1(D0, D1, A4);
Stepper stepper2(D2, D3, A3);

int ledPin = D7;

void setup()
{
  pinMode(ledPin, OUTPUT);

  Spark.function("moveTo1", moveTo1);
  Spark.function("moveTo2", moveTo2);
  Spark.function("calibrate", calibrate);
  Spark.function("lightUp", lightUp);
}

void loop()
{
  if (stepper1.isCalibrating() || stepper2.isCalibrating()) {
    digitalWrite(ledPin, HIGH);

    if (stepper1.isCalibrating()) { stepper1.calibrate(); }
    if (stepper2.isCalibrating()) { stepper2.calibrate(); }
  } else {
    digitalWrite(ledPin, LOW);
  }
}

int moveTo1(String value) {
  float newPosition = _readInput(value);
  stepper1.move(newPosition);

  return newPosition;
}

int moveTo2(String value) {
  float newPosition = _readInput(value);
  stepper2.move(newPosition);

  return newPosition;
}

int calibrate(String input) {
  if (input == "1") {
    stepper1.startCalibration();
  } else if (input == "2") {
    stepper2.startCalibration();
  }

  return 1;
}

float _readInput(String value) {
  char * valueChar = new char[value.length() + 1];
  strcpy(valueChar, value.c_str());

  return atof(valueChar);
}

int lightUp(String _value) {
  digitalWrite(ledPin, HIGH);
  delay(1000);
  digitalWrite(ledPin, LOW);

  return 1;
}

// int irSend(String value) {
//   char * valueChar = new char[value.length() + 1];
//   strcpy(valueChar, value.c_str());
//   int toSend = atof(valueChar);

//   irsend.sendSony(toSend, 12);
//   return 1;
// }
