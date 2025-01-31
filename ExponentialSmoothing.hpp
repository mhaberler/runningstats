#pragma once

#include "cmath"
#include <math.h>
#include "rstypes.h"

class ExponentialSmoothing {
  public:
    ExponentialSmoothing(_float_t alpha = 1.0) : _alpha(alpha) {
    }

    const _float_t & Alpha(void) {
        return _alpha;
    }

    void setAlpha(_float_t alpha) { // 0-1
        _alpha = alpha;
    }

    const _float_t & Value(void)  {
        return _value;
    }

    void Push(_float_t x) {
        if (isnan(_value)) {
            _value = x;
        } else {
            _value = (x * _alpha) + _value * (1 - _alpha);
        }
    }

    const _float_t &  Smooth(_float_t x) {
        Push(x);
        return _value;
    }

  private:

    _float_t _alpha;
    _float_t _value = nan("");
};

