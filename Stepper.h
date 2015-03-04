/*
  Stepper.h - Library for controlling two LED strips with PWM.
  Created by Elias S. Fatsi, March 3, 2015.
  Released into the public domain.
*/

#ifndef Stepper_h
#define Stepper_h

#include "application.h"

class Stepper
{
  public:
    Stepper(
      int dirPin,
      int stepPin,
      int buttonPin);

    void startCalibration();
    bool isCalibrating();
    void calibrate();
    void setTarget(float newTarget);
    void update();

  private:
    int _dirPin;
    int _stepPin;
    int _buttonPin;

    int   _buttonState;
    bool  _calibrating;
    float _position;
    float _targetPosition;
    float _delta;
    float _positionStep;

    void _moveTo(float newPosition);
    void _moveSteps(float steps);
};

#endif
