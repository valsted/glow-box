#ifndef _FLASHER_H
#define _FLASHER_H

class Flasher
{
    int pin = 0;
    
    bool flashing = false;
    int step = 0;
    int numSteps = 0;
    int duration = 0;

    bool isOn = false;
    unsigned long lastSwitchTime;

public:
    Flasher(int _pin) {
        pin = _pin;
        pinMode(pin, OUTPUT);
    }

    void Update() {
        if(flashing) {
            unsigned long currentTime = millis();
            if(step < numSteps) {
              if (currentTime - lastSwitchTime > duration){
                toggle();
                lastSwitchTime = currentTime;
                step++;
              }
            } else {
                off();
            }
        }
    }

    void flash(int flashDuration, int count) {
        flashing = true;
        step = 0;
        numSteps = count * 2;
        duration = flashDuration;
    }

    void off() {
        digitalWrite(pin, LOW);
        flashing = false;
    }

private: 
    void toggle() {
        if(isOn) {
            digitalWrite(pin, LOW);
            isOn = false;
        } else {
            digitalWrite(pin, HIGH);
            isOn = true;
        }
    }
};

#endif // _FLASHER_H