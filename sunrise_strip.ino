#include "fader.h"

#define WARM_LED 3 // PWM
#define COLD_LED 9 // PWM
#define BTN 2

Fader coldFader;
Fader warmFader;

State state;

long currentTime;
long targetTime;
long fadeEndTime;
const long DURATION = 30 * 1000;

void setup() {
    pinMode(WARM_LED, OUTPUT);
    pinMode(COLD_LED, OUTPUT);
    pinMode(BTN, INPUT);

    coldFader = Fader(COLD_LED);
    warmFader = Fader(WARM_LED);

    state = State::WAITING;
}

void loop() {
    currentTime = millis() >> 1;

    switch (state)
    {
        case State::ALWAYS_ON:
        case State::FADE_COMPLETE:
            analogWrite(WARM_LED, 250);
            analogWrite(COLD_LED, 240);
            break;

        case State::FADING:
            coldFader.Update();
            warmFader.Update();
            break;

        case State::WAITING:
            if (currentTime >= targetTime) {
                state = State::FADING;
                coldFader.Start(DURATION);
                warmFader.Start(DURATION);
                fadeEndTime = currentTime + DURATION;
            }
            break;
    }

    if (buttonPressed()) {

    }
}

bool buttonPressed() {
    return digitalRead(BTN) == HIGH;
}


enum State {
    ALWAYS_ON = 1, 
    WAITING = 2,
    FADING = 3,
    FADE_COMPLETE = 4
};