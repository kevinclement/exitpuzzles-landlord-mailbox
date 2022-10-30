#pragma once
#include "Arduino.h"

class Logic;

class Sound {
  public:
    Sound(Logic &logic);
    void setup();
    void handle();
    void playMail();

  private:
    Logic &_logic;
};