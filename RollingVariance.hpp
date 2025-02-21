#ifndef ROLLING_VARIANCE_H
#define ROLLING_VARIANCE_H

#include "rstypes.h"

#include <vector>

// https://stackoverflow.com/questions/5147378/rolling-variance-algorithm/74239458#74239458


class RollingVariance {
  private:
    std::vector<_float_t> _samples;
    _float_t _mean, _var_sum;
    size_t _window_size, _i;

  public:
    /**
     * @brief Constructor for RollingVariance
     * @param window_size The size of the window for variance calculation
     */
    RollingVariance(size_t window_size) : _window_size(window_size), _i(0), _mean(0.0), _var_sum(0.0) {
        _samples.resize(_window_size, 0.0);
    }

    /**
     * @brief Add a new value to the window and compute new statistics
     * @param x_new The new value to add
     */
    void Push(_float_t x_new) {
        _i = (_i + 1) % _window_size;
        _float_t x_old = _samples[_i];
        _float_t dx = x_new - x_old;  // oldest x
        _float_t new_mean = _mean + dx / (_float_t) _window_size; // new mean

        _var_sum += ((x_new + x_old - _mean - new_mean) * dx);
        _mean = new_mean;
        _samples[_i] = x_new;
    }

    _float_t Variance() const {
        return _var_sum / _window_size;
    }

    _float_t Mean(void) const {
        return _mean;
    }

    size_t getWindowSize(void) {
        return _window_size;
    }
};

#endif // ROLLING_VARIANCE_H