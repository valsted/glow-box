#ifndef _LEDBAR_H
#define _LEDBAR_H
#define PIN_COUNT 10

class LedBar
{
    bool isOn;
    int pins[PIN_COUNT];
    int *value;

public:
    LedBar(int _pins[], int* value_p) {
        value = value_p;
        for (int i = 0; i < PIN_COUNT; i++)
        {
            pins[i] = _pins[i];
            pinMode(pins[i], OUTPUT);
            digitalWrite(pins[i], HIGH);
        }
    }

    void update() {
        if (isOn) {
            for (int i = 0; i < PIN_COUNT; i++) {
                int active = i < *value ? LOW : HIGH;
                digitalWrite(pins[i], active);
            }
        }
    }

    void on() {
        isOn = true;
    }

    void off() {
        isOn = false;
    }
};

#endif // _LEDBAR_H
