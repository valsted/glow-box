#include "fader.h"
#include "ledbar.h"

#define WARM_LED 3 // PWM
#define COLD_LED 9 // PWM
#define BTN 2
#define TOGGLE 13 

enum State {
    ALWAYS_ON = 1,  // Light constant on (or fade complete)
    FADING = 2,     // Alarm in progress
    SETUP = 3,      // Listening for input.
    WAITING = 4     // Waiting for "alarm" to go off
};
State state;

Fader coldFader;
Fader warmFader;
LedBar ledBar;

// Time trackers (for fade)
long currentTime;
long targetTime;
long fadeEndTime;
const long DURATION = 30 * 1000;

// Alarm setting
int delayHours = 0;
long lastBtnPress;
const long BTN_TIMEOUT = 10 * 1000;
const long HOUR_IN_MILLISECONDS = 1000 * 60 * 60;

void setup() {
    pinMode(WARM_LED, OUTPUT);
    pinMode(COLD_LED, OUTPUT);
    pinMode(BTN, INPUT);

    coldFader = Fader(COLD_LED);
    warmFader = Fader(WARM_LED);

    int ledPins[] = { 5, 6, 7, 8, 10, 11, A0, A1, A2, A3 };
    ledBar = LedBar(ledPins, &delayHours);

    state = WAITING;
}

void loop() {
    currentTime = millis() >> 1;

    if (buttonPressed()) { 
        lastBtnPress = currentTime;
        delayHours = (delayHours + 1) % 10;
        state = SETUP;
    }

    switch (state)
    {
        case ALWAYS_ON:
            analogWrite(WARM_LED, 252);
            analogWrite(COLD_LED, 238);
            break;

        case FADING:
            coldFader.update();
            warmFader.update();
            if (coldFader.isDone() && warmFader.isDone()) {
                state = ALWAYS_ON;
            }
            break;

        case SETUP:
            warmFader.set(20);
            coldFader.set(10);
            ledBar.update();
            if (currentTime - lastBtnPress > BTN_TIMEOUT) {
                state = WAITING;
                targetTime = currentTime + ((long) delayHours * HOUR_IN_MILLISECONDS);
            }

        case WAITING:
            if (currentTime >= targetTime) {
                state = FADING;
                coldFader.start(0, 20, DURATION);
                warmFader.start(0, 90, DURATION);
                fadeEndTime = currentTime + DURATION;
            }
            break;
    }
}

bool buttonPressed() {
    return digitalRead(BTN) == HIGH;
}

bool alwaysOnToggled() {
    return digitalRead(TOGGLE) == HIGH;
}
