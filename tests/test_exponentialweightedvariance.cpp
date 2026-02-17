// Compile and run:
// g++ -std=c++17 test_exponentialweightedvariance.cpp -o test_ewvar && ./test_ewvar

#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

#define _float_t double
#include "../ExponentialWeightedVariance.hpp"

void testBasicFunctionality() {
    std::cout << "=== Test: Basic Functionality ===" << std::endl;

    ExponentialWeightedVariance<double> ewv(0.1);

    // Test initial state
    std::cout << "Initial state: mean=" << ewv.Mean()
              << ", variance=" << ewv.Variance()
              << ", count=" << ewv.NumDataValues() << std::endl;

    // Add some data points
    std::vector<double> data = {1.0, 2.0, 3.0, 4.0, 5.0};
    for (double x : data) {
        ewv.Push(x);
        std::cout << "After push(" << x << "): mean=" << std::fixed << std::setprecision(6)
                  << ewv.Mean() << ", variance=" << ewv.Variance()
                  << ", stddev=" << ewv.StandardDeviation() << std::endl;
    }

    std::cout << "Final count: " << ewv.NumDataValues() << std::endl;
    std::cout << std::endl;
}

void testConstantValues() {
    std::cout << "=== Test: Constant Values ===" << std::endl;

    ExponentialWeightedVariance<double> ewv(0.1);

    // Feed constant values - variance should approach zero
    // Need many iterations for convergence with low alpha
    for (int i = 0; i < 100; i++) {
        ewv.Push(5.0);
    }

    std::cout << "After 100 constant values (5.0):" << std::endl;
    std::cout << "Mean: " << std::fixed << std::setprecision(6) << ewv.Mean() << " (expected: ~5.0)" << std::endl;
    std::cout << "Variance: " << ewv.Variance() << " (expected: ~0.0)" << std::endl;
    std::cout << "Test " << (ewv.Variance() < 0.01 && std::abs(ewv.Mean() - 5.0) < 0.1 ? "PASSED" : "FAILED") << std::endl;
    std::cout << std::endl;
}

void testAlphaEffect() {
    std::cout << "=== Test: Alpha Effect ===" << std::endl;

    std::vector<double> data = {1.0, 2.0, 3.0, 4.0, 5.0, 10.0, 10.0, 10.0, 10.0, 10.0};

    // Test with low alpha (slow adaptation)
    ExponentialWeightedVariance<double> ewv_low(0.1);
    for (double x : data) {
        ewv_low.Push(x);
    }

    // Test with medium alpha
    ExponentialWeightedVariance<double> ewv_mid(0.5);
    for (double x : data) {
        ewv_mid.Push(x);
    }

    // Test with high alpha (fast adaptation)
    ExponentialWeightedVariance<double> ewv_high(0.9);
    for (double x : data) {
        ewv_high.Push(x);
    }

    std::cout << "After same data with different alphas:" << std::endl;
    std::cout << "Alpha=0.1: mean=" << std::fixed << std::setprecision(4) << ewv_low.Mean()
              << ", variance=" << ewv_low.Variance() << std::endl;
    std::cout << "Alpha=0.5: mean=" << ewv_mid.Mean()
              << ", variance=" << ewv_mid.Variance() << std::endl;
    std::cout << "Alpha=0.9: mean=" << ewv_high.Mean()
              << ", variance=" << ewv_high.Variance() << std::endl;

    // Higher alpha should converge closer to recent values (10.0)
    std::cout << "Test " << (ewv_high.Mean() > ewv_mid.Mean() && ewv_mid.Mean() > ewv_low.Mean() ? "PASSED" : "FAILED")
              << " (higher alpha converges faster to recent values)" << std::endl;
    std::cout << std::endl;
}

void testClearAndReset() {
    std::cout << "=== Test: Clear and Reset ===" << std::endl;

    ExponentialWeightedVariance<double> ewv(0.2);

    // Add data
    for (int i = 1; i <= 5; i++) {
        ewv.Push(i * 2.0);
    }

    std::cout << "Before clear: mean=" << ewv.Mean()
              << ", variance=" << ewv.Variance()
              << ", count=" << ewv.NumDataValues() << std::endl;

    ewv.Clear();

    std::cout << "After clear: mean=" << ewv.Mean()
              << ", variance=" << ewv.Variance()
              << ", count=" << ewv.NumDataValues() << std::endl;

    std::cout << "Test " << (ewv.Mean() == 0.0 && ewv.Variance() == 0.0 && ewv.NumDataValues() == 0 ? "PASSED" : "FAILED") << std::endl;
    std::cout << std::endl;
}

void testSetAlpha() {
    std::cout << "=== Test: Set Alpha ===" << std::endl;

    ExponentialWeightedVariance<double> ewv(0.1);

    std::cout << "Initial alpha: " << ewv.Alpha() << std::endl;

    ewv.setAlpha(0.5);
    std::cout << "After setAlpha(0.5): " << ewv.Alpha() << std::endl;

    std::cout << "Test " << (ewv.Alpha() == 0.5 ? "PASSED" : "FAILED") << std::endl;
    std::cout << std::endl;
}

void testVarianceConvergence() {
    std::cout << "=== Test: Variance Convergence ===" << std::endl;

    ExponentialWeightedVariance<double> ewv(0.2);

    // Add alternating values between 0 and 10
    for (int i = 0; i < 50; i++) {
        ewv.Push(i % 2 == 0 ? 0.0 : 10.0);
    }

    std::cout << "After 50 alternating values (0, 10, 0, 10, ...):" << std::endl;
    std::cout << "Mean: " << std::fixed << std::setprecision(4) << ewv.Mean()
              << " (expected: ~5.0)" << std::endl;
    std::cout << "Variance: " << ewv.Variance()
              << " (expected: significant, ~25)" << std::endl;
    std::cout << "Standard Deviation: " << ewv.StandardDeviation() << std::endl;

    // For alternating 0 and 10, expected variance is roughly 25
    std::cout << "Test " << (std::abs(ewv.Mean() - 5.0) < 1.0 && ewv.Variance() > 10.0 ? "PASSED" : "FAILED") << std::endl;
    std::cout << std::endl;
}

void testSingleValue() {
    std::cout << "=== Test: Single Value ===" << std::endl;

    ExponentialWeightedVariance<double> ewv(0.3);
    ewv.Push(7.5);

    std::cout << "After single value (7.5):" << std::endl;
    std::cout << "Mean: " << ewv.Mean() << " (expected: 2.25)" << std::endl;
    std::cout << "Variance: " << ewv.Variance() << " (expected: 11.8125)" << std::endl;
    std::cout << "Count: " << ewv.NumDataValues() << std::endl;

    // After one value with alpha=0.3: mean = 0.3 * 7.5 = 2.25, variance = 0.7 * (7.5 * 2.25) = 11.8125
    std::cout << "Test " << (std::abs(ewv.Mean() - 2.25) < 0.0001 && std::abs(ewv.Variance() - 11.8125) < 0.0001 && ewv.NumDataValues() == 1 ? "PASSED" : "FAILED") << std::endl;
    std::cout << std::endl;
}

int main() {
    std::cout << "========================================" << std::endl;
    std::cout << "ExponentialWeightedVariance Test Suite" << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << std::endl;

    testBasicFunctionality();
    testConstantValues();
    testAlphaEffect();
    testClearAndReset();
    testSetAlpha();
    testVarianceConvergence();
    testSingleValue();

    std::cout << "========================================" << std::endl;
    std::cout << "All tests completed!" << std::endl;
    std::cout << "========================================" << std::endl;

    return 0;
}
