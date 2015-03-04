#include "IRremote.h"
#include "Stepper.h"

IRsend irsend(D6);

Stepper stepper1(D0, D1, A4);
Stepper stepper2(D2, D3, A3);

int ledPin = D5;

void setup()
{
  pinMode(ledPin, OUTPUT);

  Spark.function("moveBoth", moveBoth);
  Spark.function("moveTo1", moveTo1);
  Spark.function("moveTo2", moveTo2);
  Spark.function("calibrate", calibrate);
}

void loop() {
  calibrationCheck();

  stepper1.update();
  stepper2.update();
}

int moveBoth(String input) {
  int loc1 = 0;
  int loc2 = 0;
  float arg1;
  float arg2;

  loc1 = input.indexOf(",");
  arg1 = input.substring(0, loc1).toFloat();

  loc2 = input.indexOf(",", loc1 + 1);
  arg2 = input.substring(loc1 + 1, loc2).toFloat();

  stepper1.setTarget(arg1);
  stepper2.setTarget(arg2);

  return arg1 + arg2;
}

int moveTo1(String value) {
  float newPosition = value.toFloat();
  stepper1.setTarget(newPosition);

  return newPosition;
}

int moveTo2(String value) {
  float newPosition = value.toFloat();
  stepper2.setTarget(newPosition);

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

void calibrationCheck() {
  if (stepper1.isCalibrating() || stepper2.isCalibrating()) {
    digitalWrite(ledPin, HIGH);

    if (stepper1.isCalibrating()) { stepper1.calibrate(); }
    if (stepper2.isCalibrating()) { stepper2.calibrate(); }
  } else {
    digitalWrite(ledPin, LOW);
  }
}

// int irSend(String value) {
//   char * valueChar = new char[value.length() + 1];
//   strcpy(valueChar, value.c_str());
//   int toSend = atof(valueChar);

//   irsend.sendSony(toSend, 12);
//   return 1;
// }
