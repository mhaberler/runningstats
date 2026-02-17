#pragma once

#include "rstypes.h"
#include <cmath>

/**
 * Exponentially Weighted Moving Variance (EWMV)
 * Computes variance with exponentially decaying weights on historical data
 *
 * Based on: https://grok.com/share/bGVnYWN5_86b4d8af-96c7-40f3-9de2-cc1b0e9d975c
 *
 * The algorithm maintains both an exponentially weighted moving average (EWMA)
 * for the mean and an EWMA for the variance using the online update formula:
 *   diff = x - mean
 *   incr = alpha * diff
 *   mean = mean + incr
 *   variance = (1 - alpha) * (variance + diff * incr)
 *
 * where alpha is the weight on new data (0 < alpha <= 1).
 * Higher alpha = more responsive to recent changes
 * Lower alpha = smoother, more historical weight
 */
template <typename T = _float_t>
class ExponentialWeightedVariance {
public:
    /**
     * @brief Constructor
     * @param alpha Weight on new data (0 < alpha <= 1), defaults to 0.1
     */
    ExponentialWeightedVariance(T alpha = 0.1) : _alpha(alpha), _mean(0.0), _var(0.0), _count(0) {
    }

    /**
     * @brief Get the current alpha (weight on new data)
     * @return The alpha value
     */
    const T& Alpha() const {
        return _alpha;
    }

    /**
     * @brief Set the alpha (weight on new data)
     * @param alpha Weight on new data (0 < alpha <= 1)
     */
    void setAlpha(T alpha) {
        _alpha = alpha;
    }

    /**
     * @brief Get the current exponentially weighted mean
     * @return The mean value
     */
    const T& Mean() const {
        return _mean;
    }

    /**
     * @brief Get the current exponentially weighted variance
     * @return The variance value
     */
    const T& Variance() const {
        return _var;
    }

    /**
     * @brief Get the standard deviation
     * @return The standard deviation (sqrt of variance)
     */
    T StandardDeviation() const {
        return std::sqrt(_var);
    }

    /**
     * @brief Get the number of data points processed
     * @return Number of data points
     */
    _counter_t NumDataValues() const {
        return _count;
    }

    /**
     * @brief Add a new data point and update the statistics
     * @param x The new value to add
     */
    void Push(T x) {
        T diff = x - _mean;
        T incr = _alpha * diff;
        _mean += incr;
        _var = (1.0 - _alpha) * (_var + diff * incr);
        _count++;
    }

    /**
     * @brief Reset all statistics to initial state
     */
    void Clear() {
        _mean = 0.0;
        _var = 0.0;
        _count = 0;
    }

private:
    T _alpha;        // Weight on new data (0 < alpha <= 1)
    T _mean;         // Exponentially weighted moving average
    T _var;          // Exponentially weighted moving variance
    _counter_t _count; // Number of data points processed
};
