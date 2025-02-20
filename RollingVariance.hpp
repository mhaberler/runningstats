#ifndef ROLLING_VARIANCE_H
#define ROLLING_VARIANCE_H

#include "rstypes.h"

#include <vector>

// https://stackoverflow.com/questions/5147378/rolling-variance-algorithm/74239458#74239458


class RollingVariance {
private:
    std::vector<_float_t> _samples;
    _float_t _mean, _var;
    size_t _n, _i;

public:
    /**
     * @brief Constructor for RollingVariance
     * @param size The size of the window for variance calculation
     */
    RollingVariance(size_t window_size) : _n(window_size), _mean(0.0), _var(0.0) {
        _samples.resize(_n, 0.0);
    }

    /**
     * @brief Add a new value to the window and compute new statistics
     * @param value The new value to add
     */
    void add(double x) {
        _i = (_i + 1) % _n;
        _float_t xold = _samples[_i];
        _float_t dx = x - xold;  // oldest x
        _float_t nmean = _mean + dx / (_float_t) _n; // new mean
        //_var += ((x - _mean)*(x - nmean) - (xold - _mean) * (xold - nmean)) / (float) _n;
        _var += ((x + xold - _mean - nmean) * dx) / (_float_t) _n;
        _mean = nmean;
        _samples[_i] = x;
    }

    /**
     * @brief Compute the variance of the values in the window
     * @return The variance of the current window
     */
    _float_t variance() const {
        return _var;
    }

    /**
     * @brief Get the current mean of the window
     * @return The mean value
     */
    _float_t mean() const {
        return _mean;
    }
};

#endif // ROLLING_VARIANCE_H