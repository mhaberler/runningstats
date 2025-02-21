// from: https://www.johndcook.com/blog/skewness_kurtosis/


// templated version of RunningStats to just do Variance and Mean

#pragma once


#include <cmath>
#include <cstddef> // for size_t

template <typename T, typename CounterT = size_t>
class RunningVariance {
public:
    RunningVariance() { Clear(); }

    /**
     * @brief Reset all statistics to initial state
     */
    void Clear() {
        n = 0;
        M1 = M2 = static_cast<T>(0.0);
    }

    /**
     * @brief Add a new value to the statistics
     * @param x The value to add
     */
    void Push(T x) {
        T delta, delta_n, term1;
        CounterT n1 = n;
        n++;
        delta = x - M1;
        delta_n = delta / static_cast<T>(n);
        term1 = delta * delta_n * static_cast<T>(n1);
        M1 += delta_n;
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

   
private:
    CounterT n; // Number of values
    T M1, M2; // Moments
};

