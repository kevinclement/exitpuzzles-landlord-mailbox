#pragma once
#include "Arduino.h"

class Logic;

class Vacuum {
  public:
    Vacuum(Logic &logic);
    void setup();
    void handle();
    void toggle();
    void on();
    void off();
    String status();

  private:
    Logic &_logic;
    bool relayOn = false;
};