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
    void move(int newPosition);
  private:
    int _dirPin;
    int _stepPin;
    int _buttonPin;

    int  _buttonState;
    int  _position;
    bool _calibrating;

    void _movement(int steps);
};

#endif
