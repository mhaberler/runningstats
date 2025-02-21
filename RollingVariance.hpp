#ifndef ROLLING_VARIANCE_H
#define ROLLING_VARIANCE_H

#include <vector>

template <typename T>
class RollingVariance {
private:
    std::vector<T> _samples;
    T _mean, _var_sum;
    size_t _window_size, _i;

public:
    /**
     * @brief Constructor for RollingVariance
     * @param window_size The size of the window for variance calculation
     */
    RollingVariance(size_t window_size) 
        : _window_size(window_size), _i(0), _mean(static_cast<T>(0.0)), _var_sum(static_cast<T>(0.0)) {
        _samples.resize(_window_size, static_cast<T>(0.0));
    }

    /**
     * @brief Reset the instance to its initial state
     */
    void Clear() {
        _i = 0;
        _mean = static_cast<T>(0.0);
        _var_sum = static_cast<T>(0.0);
        std::fill(_samples.begin(), _samples.end(), static_cast<T>(0.0));
    }

    /**
     * @brief Add a new value to the window and compute new statistics
     * @param x_new The new value to add
     */
    void Push(T x_new) {
        _i = (_i + 1) % _window_size;
        T x_old = _samples[_i];
        T dx = x_new - x_old;  // oldest x
        T new_mean = _mean + dx / static_cast<T>(_window_size); // new mean

        _var_sum += ((x_new + x_old - _mean - new_mean) * dx);
        _mean = new_mean;
        _samples[_i] = x_new;
    }

    /**
     * @brief Compute the variance of the current window
     * @return The variance
     */
    T Variance() const {
        return _var_sum / static_cast<T>(_window_size);
    }

    /**
     * @brief Get the current mean of the window
     * @return The mean value
     */
    T Mean() const {
        return _mean;
    }

    /**
     * @brief Get the window size
     * @return The size of the window
     */
    size_t getWindowSize() const {
        return _window_size;
    }
};

#endif // ROLLING_VARIANCE_H