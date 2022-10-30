#include "Arduino.h"
#include "logic.h"
#include "Audio.h"
#include "SPIFFS.h"

#define I2S_DOUT  	A1    // BROWN  => 25 A1
#define I2S_BCLK   	A10   // ORANGE => 27 A10
#define I2S_LRC    	A0    // BLUE   => 26 A0

Audio audio;

Sound::Sound(Logic &logic)
: _logic(logic)
{
}

void Sound::setup() {
    if(!SPIFFS.begin(true)){
        Serial.println("An Error has occurred while mounting SPIFFS");
        return;
    }

    audio.setPinout(I2S_BCLK, I2S_LRC, I2S_DOUT);
    audio.setBalance(-16); // mutes the left channel
    audio.setVolume(21);   // max loudness
}

void Sound::handle() {
    audio.loop();
}

void Sound::playMail() {
    audio.connecttoFS(SPIFFS, "003-youve-got-mail.wav");
}

void Sound::playJetsons() {
    audio.connecttoFS(SPIFFS, "002-jetsons.mp3");
}

void Sound::playWorms() {
    audio.connecttoFS(SPIFFS, "001-worms-incoming.mp3");
}