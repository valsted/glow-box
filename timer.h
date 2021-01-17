#ifndef _TIMER_H
#define _TIMER_H

class Timer
{
  unsigned long start;
  unsigned long end;

public:
    Timer() { }

    bool elapsed() {
      return millis() > end;
    }

    void start(unsigned long duration) {
      start = millis();
      end = start + duration;
    }
};

#endif // _TIMER_H