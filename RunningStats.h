// from: https://www.johndcook.com/blog/skewness_kurtosis/

#ifndef RUNNING_STATS_H
#define RUNNING_STATS_H

#include <cmath>
#include <cstddef> // for size_t

// Confidence interval enum
enum class CI : int {
    CI90 = 0,
    CI95,
    CI99
};

template <typename T, typename CounterT = size_t>
class RunningStats {
public:
    RunningStats() { Clear(); }

    /**
     * @brief Reset all statistics to initial state
     */
    void Clear() {
        n = 0;
        M1 = M2 = M3 = M4 = static_cast<T>(0.0);
    }

    /**
     * @brief Add a new value to the statistics
     * @param x The value to add
     */
    void Push(T x) {
        T delta, delta_n, delta_n2, term1;
        CounterT n1 = n;
        n++;
        delta = x - M1;
        delta_n = delta / static_cast<T>(n);
        delta_n2 = delta_n * delta_n;
        term1 = delta * delta_n * static_cast<T>(n1);
        M1 += delta_n;
        M4 += term1 * delta_n2 * (static_cast<T>(n * n) - static_cast<T>(3 * n) + static_cast<T>(3)) +
              static_cast<T>(6) * delta_n2 * M2 - static_cast<T>(4) * delta_n * M3;
        M3 += term1 * delta_n * (static_cast<T>(n) - static_cast<T>(2)) - static_cast<T>(3) * delta_n * M2;
        M2 += term1;
    }

    /**
     * @brief Get the number of values added
     * @return Number of data points
     */
    CounterT NumDataValues() const { return n; }

    /**
     * @brief Get the mean of the values
     * @return The mean
     */
    T Mean() const { return M1; }

    /**
     * @brief Get the sample variance (n-1 denominator)
     * @return The sample variance
     */
    T Variance() const { return (n > 1) ? M2 / static_cast<T>(n - 1) : static_cast<T>(0.0); }

    /**
     * @brief Get the population variance (n denominator)
     * @return The population variance
     */
    T PopulationVariance() const { return (n > 0) ? M2 / static_cast<T>(n) : static_cast<T>(0.0); }

    /**
     * @brief Get the sample standard deviation
     * @return The standard deviation
     */
    T StandardDeviation() const { return std::sqrt(Variance()); }

    /**
     * @brief Get the skewness of the distribution
     * @return The skewness
     */
    T Skewness() const {
        return (n > 0) ? std::sqrt(static_cast<T>(n)) * M3 / std::pow(M2, static_cast<T>(1.5)) : static_cast<T>(0.0);
    }

    /**
     * @brief Get the kurtosis of the distribution (excess kurtosis)
     * @return The kurtosis
     */
    T Kurtosis() const {
        return (n > 0) ? static_cast<T>(n) * M4 / (M2 * M2) - static_cast<T>(3.0) : static_cast<T>(0.0);
    }

    /**
     * @brief Compute the confidence interval for the mean
     * @param ci Confidence level (CI90, CI95, CI99)
     * @return The confidence interval width
     */
    T ConfidenceInterval(CI ci) {
        static constexpr T z_values[] = {static_cast<T>(1.645), static_cast<T>(1.960), static_cast<T>(2.576)};
        return z_values[static_cast<int>(ci)] * StandardDeviation() / std::sqrt(static_cast<T>(n));
    }

    /**
     * @brief Combine two RunningStats objects
     * @param a First stats object
     * @param b Second stats object
     * @return Combined stats object
     */
    friend RunningStats operator+(const RunningStats& a, const RunningStats& b) {
        RunningStats combined;

        combined.n = a.n + b.n;
        if (combined.n == 0) return combined;

        T delta = b.M1 - a.M1;
        T delta2 = delta * delta;
        T delta3 = delta * delta2;
        T delta4 = delta2 * delta2;

        combined.M1 = (static_cast<T>(a.n) * a.M1 + static_cast<T>(b.n) * b.M1) / static_cast<T>(combined.n);

        combined.M2 = a.M2 + b.M2 + delta2 * static_cast<T>(a.n) * static_cast<T>(b.n) / static_cast<T>(combined.n);

        combined.M3 = a.M3 + b.M3 +
                      delta3 * static_cast<T>(a.n) * static_cast<T>(b.n) * static_cast<T>(a.n - b.n) /
                          (static_cast<T>(combined.n * combined.n));
        combined.M3 += static_cast<T>(3.0) * delta * (static_cast<T>(a.n) * b.M2 - static_cast<T>(b.n) * a.M2) /
                       static_cast<T>(combined.n);

        combined.M4 = a.M4 + b.M4 +
                      delta4 * static_cast<T>(a.n) * static_cast<T>(b.n) *
                          (static_cast<T>(a.n * a.n) - static_cast<T>(a.n * b.n) + static_cast<T>(b.n * b.n)) /
                          (static_cast<T>(combined.n * combined.n * combined.n));
        combined.M4 += static_cast<T>(6.0) * delta2 * (static_cast<T>(a.n * a.n) * b.M2 + static_cast<T>(b.n * b.n) * a.M2) /
                           (static_cast<T>(combined.n * combined.n)) +
                       static_cast<T>(4.0) * delta * (static_cast<T>(a.n) * b.M3 - static_cast<T>(b.n) * a.M3) /
                           static_cast<T>(combined.n);

        return combined;
    }

    /**
     * @brief Add another RunningStats object to this one
     * @param rhs The object to add
     * @return Reference to this object
     */
    RunningStats& operator+=(const RunningStats& rhs) {
        *this = *this + rhs;
        return *this;
    }

private:
    CounterT n; // Number of values
    T M1, M2, M3, M4; // Moments
};

#endif // RUNNING_STATS_H