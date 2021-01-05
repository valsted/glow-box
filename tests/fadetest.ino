#include "../fader.h"

#define WARM_LED 3 // PWM
#define COLD_LED 9 // PWM

Fader coldFader;
Fader warmFader;

void setup() {
    pinMode(WARM_LED, OUTPUT);
    pinMode(COLD_LED, OUTPUT);

    coldFader = Fader(COLD_LED);
    warmFader = Fader(WARM_LED);
}

void loop() {
    // COLD
    // Fade up
    coldFader.start(0, 80, 5 * 1000);
    while(!coldFader.isDone()) {
        coldFader.update();
    }

    // Fade down
    coldFader.start(80, 0, 5 * 1000);
    while(!coldFader.isDone()) {
        coldFader.update();
    }

    // WARM
    /// Fade up
    warmFader.start(0, 90, 5 * 1000);
    while(!warmFader.isDone()) {
        warmFader.update();
    }

    // Fade down
    warmFader.start(90, 0, 5 * 1000);
    while(!warmFader.isDone()) {
        warmFader.update();
    }
}