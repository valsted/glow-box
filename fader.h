#ifndef _FADER_H
#define _FADER_H

class Fader
{
    int PIN;
    long curTime;
    long startTime;
    long endTime;
    bool fading;

public:
    Fader(int pin)
    {
        PIN = pin;
        pinMode(PIN, OUTPUT);
        fading = false;
        curTime = 0;
    }

    void Update()
    {
        if (fading)
        {
            curTime = millis() >> 1;
            if (curTime < endTime)
            {
                int val = map(curTime, startTime, endTime, 0, 250);
                analogWrite(PIN, val);
            }
            else
            {
                reset();
            }
        }
    }

    void Start(unsigned long duration)
    {
        startTime = millis() >> 1;
        endTime = startTime + (duration >> 1);
        curTime = startTime;
        fading = true;
    }

private:
    void reset()
    {
        fading = false;
        endTime = startTime = curTime = 0;
        analogWrite(PIN, 0);
    }
};

#endif // _FADER_H
