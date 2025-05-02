#pragma once

#include "RunningStats.hpp"
#include "esp_timer.h"
#include "fmicro.h"


// This class provides:

// Push(): Records an event and calculates the instantaneous rate based on time between events
// Clear(): Resets all statistics and timing information
// TimeSinceLastPush(): Returns seconds since the last event

// The class measures instantaneous rates between consecutive events and maintains running statistics of these rates. The mean value represents the average events per second over the measurement period.

// // Call Push() whenever your event occurs
// rates.Push();  // First push establishes baseline time
// rates.Push();  // Second and subsequent pushes calculate rates

// // Get statistics about the rates
// float avgRate = rates.Mean();     // Average events per second
// float maxRate = rates.Maximum();  // Maximum rate seen
// float stdDev = rates.StandardDeviation();  // Variation in the rate

class RateStats : public RunningStats {
  public:
    // Push an event and calculate rate since last push
    void Push() {
        uint32_t now = dmicros();
        if (!std::isnan(_lastPushTime)) {
            // Convert microseconds to seconds and calculate rate (events/second)
            float deltaSeconds = (now - _lastPushTime) / 1000000.0f;
            if (deltaSeconds > 0) {
                // Rate = 1/time between events
                RunningStats::Push(1.0f / deltaSeconds);
            }
        }
        _lastPushTime = now;
    }

    // Reset the stats and timing
    void Clear() {
        _lastPushTime = NAN;
        RunningStats::Clear();
    }

    // Get time since last push in seconds
    float TimeSinceLastPush() {
        if (std::isnan(_lastPushTime)) return NAN;
        return (dmicros() - _lastPushTime) / 1000000.0f;
    }

  private:
    _float_t _lastPushTime = NAN;
};

