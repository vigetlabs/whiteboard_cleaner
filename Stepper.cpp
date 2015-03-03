/*
  Stepper.h - Library for controlling Whiteboard Cleaning stepper motors.
  Created by Elias S. Fatsi, March 3, 2015.
  Released into the public domain.
*/

#include "Stepper.h"

Stepper::Stepper(
  int dirPin,
  int stepPin,
  int buttonPin,
  bool invert)
{
  _dirPin    = dirPin;
  _stepPin   = stepPin;
  _buttonPin = buttonPin;

  _buttonState = 0;
  _position    = 0;
  _calibrating = false;

  if (invert) {
    _inward  = HIGH;
    _outward = LOW;
  } else {
    _inward  = LOW;
    _outward = HIGH;
  }

  analogWrite(_dirPin,    OUTPUT);
  analogWrite(_stepPin,   OUTPUT);
  analogWrite(_buttonPin, OUTPUT);
}

void Stepper::startCalibration() {
  _calibrating = true;
}

bool Stepper::isCalibrating() {
  return _calibrating;
}

void Stepper::calibrate() {
  _buttonState = digitalRead(_buttonPin);

  digitalWrite(_dirPin, LOW);
  _movement(20);

  if (_buttonState == HIGH) {
    _calibrating = false;
    _position    = 0;
  }
}

void Stepper::move(int newPosition)
{
  if(newPosition > _position) {
    digitalWrite(_dirPin, HIGH);
    _movement((newPosition - _position) * 1600);
  } else {
    digitalWrite(_dirPin, LOW);
    _movement((_position - newPosition) * 1600);
  }

  _position = newPosition;
}

void Stepper::_movement(int steps) {
  for (int i = 0; i < steps; i++) {
    digitalWrite(_stepPin, LOW);
    digitalWrite(_stepPin, HIGH);
    delayMicroseconds(500);
  }
}
