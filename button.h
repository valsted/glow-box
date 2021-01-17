#ifndef _BUTTON_H
#define _BUTTON_H

class Button
{
    int pin = 0;
    int onValue = HIGH;

public:
    Button(int _pin, int _onValue) {
        pin = _pin;
        onValue = _onValue;
        pinMode(pin, INPUT);
    }

    bool isPressed() {
        return digitalRead(pin) == onValue;
    }
};

#endif // _BUTTON_H