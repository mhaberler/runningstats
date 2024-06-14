#pragma once

#include "cmath"
#include <math.h>

class ExponentialSmoothing {
  public:
    ExponentialSmoothing(double alpha = 1.0) : _alpha(alpha) {
    }

    const double & Alpha(void) {
        return _alpha;
    }

    void setAlpha(double alpha) { // 0-1
        _alpha = alpha;
    }

    const double & Value(void)  {
        return _value;
    }

    void Push(double x) {
        if (isnan(_value)) {
            _value = x;
        } else {
            _value = (x * _alpha) + _value * (1 - _alpha);
        }
    }

    const double &  Smooth(double x) {
        Push(x);
        return _value;
    }

  private:

    double _alpha;
    double _value = nan("");
};

