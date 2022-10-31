#pragma once
#include "Arduino.h"

class Logic;

class ResetButton {
  public:
    ResetButton(Logic &logic);
    void setup();
    void handle();
    
    bool pressed = false;

  private:
    Logic &_logic;
};