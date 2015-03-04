/*
  Stepper.h - Library for controlling Whiteboard Cleaning stepper motors.
  Created by Elias S. Fatsi, March 3, 2015.
  Released into the public domain.
*/

#include "Stepper.h"

Stepper::Stepper(
  int dirPin,
  int stepPin,
  int buttonPin)
{
  _dirPin    = dirPin;
  _stepPin   = stepPin;
  _buttonPin = buttonPin;

  _buttonState    = 0;
  _position       = 0;
  _targetPosition = 0;
  _calibrating    = false;
  _buffer          = 0.005;
  _positionStep   = 0.0075;

  pinMode(_dirPin,    OUTPUT);
  pinMode(_stepPin,   OUTPUT);
  pinMode(_buttonPin, INPUT);
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
  _moveSteps(80);

  if (_buttonState == HIGH) {
    _calibrating    = false;
    _position       = 0;
    _targetPosition = 0;
  }
}

void Stepper::setTarget(float newTarget) {
  _targetPosition = newTarget;
}

void Stepper::update() {
  if (_targetPosition > (_position + _buffer)) {
    _moveTo(_position + _positionStep);
  } else if (_targetPosition < (_position - _buffer)) {
    _moveTo(_position - _positionStep);
  }
}

void Stepper::_moveTo(float newPosition)
{
  if(newPosition > _position) {
    digitalWrite(_dirPin, HIGH);
    _moveSteps((newPosition - _position) * 1600);
  } else {
    digitalWrite(_dirPin, LOW);
    _moveSteps((_position - newPosition) * 1600);
  }

  _position = newPosition;
}

void Stepper::_moveSteps(float steps) {
  for (int i = 0; i < steps; i++) {
    digitalWrite(_stepPin, LOW);
    digitalWrite(_stepPin, HIGH);
    delayMicroseconds(500);
  }
}
