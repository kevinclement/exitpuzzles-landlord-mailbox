#pragma once

#include "Arduino.h"
#include "vacuum.h"
#include "servo.h"
#include "resetButton.h"

enum State { WAITING, STARTING, DROPPING, SETTLING, DONE };

class Logic {
public:
  Logic();
  Vacuum vacuum;
  MyServo servo;
  ResetButton resetButton;
  
  void setup();
  void handle();
  void trigger();
  void status();
  void reset();
  
private:
  bool handledResetPressed = false;
  State state = WAITING;
};

