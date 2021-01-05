#ifndef _FADER_H
#define _FADER_H

class Fader
{
    int PIN;
    long curTime;
    long startTime;
    long endTime;
    bool fading;

    // 0-100;
    int startIntensity; 
    int endIntensity;

public:
    Fader(int pin) {
        PIN = pin;
        pinMode(PIN, OUTPUT);
        fading = false;
        curTime = 0;
    }

    void update() {
        if (fading) {
            curTime = millis() >> 1;
            if (curTime < endTime) {
                int val = map(curTime, startTime, endTime, startIntensity, endIntensity);
                analogWrite(PIN, val);
            } else {
                analogWrite(PIN, endIntensity);
            }
        }
    }

    void start(int intensity, int targetIntensity, unsigned long duration) {
        fading = true;  
        startIntensity = intensity;
        endIntensity = targetIntensity;
        analogWrite(PIN, startIntensity);

        startTime = millis() >> 1;
        endTime = startTime + (duration >> 1);
        curTime = startTime;
    }

    void set(int intensity) {
        reset();
        int val = map(intensity, 0, 100, 0, 255);
        analogWrite(PIN, val);
    }

    void reset() {
        fading = false;
        startIntensity = endIntensity = 0;
        endTime = startTime = curTime = 0;
        analogWrite(PIN, 0);
    }

    bool isDone() {
        return !fading || currentTime > endTime;
    }
};

#endif // _FADER_H
