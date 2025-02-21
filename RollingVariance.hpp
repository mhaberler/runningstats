#ifndef ROLLING_VARIANCE_H
#define ROLLING_VARIANCE_H

#include "rstypes.h"

#include <vector>

// https://stackoverflow.com/questions/5147378/rolling-variance-algorithm/74239458#74239458


class RollingVariance {
  private:
    std::vector<_float_t> _samples;
    _float_t _mean, _pop_var, _sample_var;
    size_t _n, _i;

  public:
    /**
     * @brief Constructor for RollingVariance
     * @param size The size of the window for variance calculation
     */
    RollingVariance(size_t window_size) : _n(window_size), _i(0), _mean(0.0), _pop_var(0.0), _sample_var(0.0) {
        _samples.resize(_n, 0.0);
    }

    /**
     * @brief Add a new value to the window and compute new statistics
     * @param value The new value to add
     */
    void Push(_float_t x) {
        _i = (_i + 1) % _n;
        _float_t xold = _samples[_i];
        _float_t dx = x - xold;  // oldest x
        _float_t nmean = _mean + dx / (_float_t) _n; // new mean
        //_pop_var += ((x - _mean)*(x - nmean) - (xold - _mean) * (xold - nmean)) / (float) _n;
        // _pop_var += ((x + xold - _mean - nmean) * dx) / (_float_t) _n;
        _float_t d = (x + xold - _mean - nmean) * dx;

        _pop_var += d / _n;
        _sample_var += d / (_n - 1);
        _mean = nmean;
        _samples[_i] = x;
    }

    _float_t PopulationVariance() const {
        return _pop_var;
    }

    _float_t Variance() const {
        return _sample_var;
    }

    _float_t Mean(void) const {
        return _mean;
    }

    size_t getWindowSize(void) {
        return _n;
    }
};

#endif // ROLLING_VARIANCE_H