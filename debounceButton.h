#ifndef _DEBOUNCE_BUTTON_H
#define _DEBOUNCE_BUTTON_H

class DebounceButton
{
    int pin = 0;
    unsigned long lastPress = 0l;
    unsigned long debouncetTime = 2; // ms
    int onValue = HIGH;

public:
    DebounceButton(int _pin, int _onValue) {
        pin = _pin;
        onValue = _onValue;
        pinMode(pin, INPUT);
    }

    bool isPressed() {
        unsigned long curTime = millis();
        bool result = digitalRead(pin) == onValue && lastPress - curTime > debouncetTime;
        lastPress = millis();
        return result;
    }
};

#endif // _DEBOUNCE_BUTTON_H