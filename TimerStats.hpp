#ifndef TIMERSTATS_H
#define TIMERSTATS_H

#include "RunningStats.hpp"
#include "esp_timer.h"
#include "fmicro.h"


class TimerStats : public RunningStats {
  public:

    // interval timing: accumulate stats for duration between
    // pairs of Start()/Stop() calls:
    void Start() {
        _starttime = dmicros();
    }
    void Stop() {
        Push(dmicros() - _starttime);
    }

    // or use as a lap timer: measure stats for time between Lap() calls
    void Lap() {
        if (_laptime == 0) {
            _laptime = dmicros();
        } else {
            uint32_t now = dmicros();
            Push(now - _laptime);
            _laptime = now;
        }
    }
    void Clear() {
        _laptime = 0;
        RunningStats::Clear();
    }

  private:
    double _starttime;
    double _laptime;
};

#endif