#ifndef ONLINE_VARIANCE_H
#define ONLINE_VARIANCE_H

#include <cmath>
#include <deque>

class OnlineVariance {
private:
    std::deque<double> window;
    size_t window_size;
    double mean;
    double M2; // Sum of squares of differences from the (current) mean
    size_t count;

public:
    /**
     * @brief Constructor for OnlineVariance
     * @param size The size of the window for variance calculation
     */
    OnlineVariance(size_t size) : window_size(size), mean(0.0), M2(0.0), count(0) {}

    /**
     * @brief Add a new value to the window and compute new statistics
     * @param value The new value to add
     */
    void update(double value) {
        if (count < window_size) {
            ++count;
        } else {
            // Remove oldest value from statistics
            double oldest = window.back();
            double old_mean = mean;
            mean -= (oldest - mean) / window_size;
            M2 -= (oldest - old_mean) * (oldest - mean);
            window.pop_back();
        }

        // Add new value to statistics
        window.push_front(value);
        double old_mean = mean;
        mean += (value - mean) / count;
        M2 += (value - old_mean) * (value - mean);
    }

    /**
     * @brief Compute the variance of the values in the window
     * @return The variance of the current window
     */
    double variance() const {
        if (count < 2) {
            return 0.0; // Variance is undefined for less than two samples
        }
        return M2 / (count - 1);
    }

    /**
     * @brief Get the current mean of the window
     * @return The mean value
     */
    double getMean() const {
        return mean;
    }

    /**
     * @brief Check if the window is full
     * @return True if the number of elements equals window_size, false otherwise
     */
    bool isFull() const {
        return count == window_size;
    }
};

#endif // ONLINE_VARIANCE_H