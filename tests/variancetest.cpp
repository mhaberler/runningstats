// g++ -std=c++17 variancetest.cpp ../RunningStats.cpp

#include <iostream>
#include <vector>
#include <cassert>
#include <cmath>

#include "../WelfordVariance.hpp"
#include "../RunningStats.hpp"

math::WelfordVariance<float> wv;
RunningStats rs;

double calculateVariance(const std::vector<double>& data) {
    if (data.empty()) return std::nan(""); // Return NaN for empty set
    double sum = 0.0;
    for (double x : data) sum += x;
    double mean = sum / data.size();
    double squaredDiffSum = 0.0;
    for (double x : data) squaredDiffSum += (x - mean) * (x - mean);
    return squaredDiffSum / data.size(); // Population variance
}

void runTest(const std::vector<double>& data, double expected, const std::string& testName) {
    double result = calculateVariance(data);
    std::cout << "Test: " << testName << " - ";
    if (data.empty()) {
        if (std::isnan(result) && std::isnan(expected)) {
            std::cout << "Passed (NaN)\n";
        } else {
            std::cout << "Failed (Expected NaN, Got " << result << ")\n";
        }
    } else {
        double tolerance = 1e-6; // For floating-point comparison
        if (std::abs(result - expected) < tolerance) {
            std::cout << "Passed (Result: " << result << ")\n";
        } else {
            std::cout << "Failed (Expected: " << expected << ", Got: " << result << ")\n";
        }
    }

    wv.clear();
    for (double x : data) wv.add(x);
    result = wv.getPopulationVariance();
    std::cout << "Test wv: " << testName << " - ";
    if (data.empty()) {
        if (std::isnan(result) && std::isnan(expected)) {
            std::cout << "Passed (NaN)\n";
        } else {
            std::cout << "Failed (Expected NaN, Got " << result << ")\n";
        }
    } else {
        double tolerance = 1e-6; // For floating-point comparison
        if (std::abs(result - expected) < tolerance) {
            std::cout << "Passed (Result: " << result << ")\n";
        } else {
            std::cout << "Failed (Expected: " << expected << ", Got: " << result << ")\n";
        }
    }
    math::RollingWelfordVariance<float> rwv(5);

    for (double x : data) rwv.add(x);
    result = rwv.getPopulationVariance();
    std::cout << "Test rwv: " << testName << " - ";
    if (data.empty()) {
        if (std::isnan(result) && std::isnan(expected)) {
            std::cout << "Passed (NaN)\n";
        } else {
            std::cout << "Failed (Expected NaN, Got " << result << ")\n";
        }
    } else {
        double tolerance = 1e-6; // For floating-point comparison
        if (std::abs(result - expected) < tolerance) {
            std::cout << "Passed (Result: " << result << ")\n";
        } else {
            std::cout << "Failed (Expected: " << expected << ", Got: " << result << ")\n";
        }
    }

    rs.Clear();
    for (double x : data) rs.Push(x);
    result = wv.getPopulationVariance();
    std::cout << "Test rs: " << testName << " - ";
    if (data.empty()) {
        if (std::isnan(result) && std::isnan(expected)) {
            std::cout << "Passed (NaN)\n";
        } else {
            std::cout << "Failed (Expected NaN, Got " << result << ")\n";
        }
    } else {
        double tolerance = 1e-6; // For floating-point comparison
        if (std::abs(result - expected) < tolerance) {
            std::cout << "Passed (Result: " << result << ")\n";
        } else {
            std::cout << "Failed (Expected: " << expected << ", Got: " << result << ")\n";
        }
    }
    
}

int main() {
    // Test cases
    runTest({}, std::nan(""), "Empty Set");
    runTest({5}, 0.0, "Single Element");
    runTest({3, 3, 3, 3}, 0.0, "All Identical");
    runTest({1, 2, 3, 4, 5}, 2.0, "Small Positive Integers");
    runTest({-2, -1, 0, 1, 2}, 2.0, "Negative Numbers");
    runTest({1, 1000, 1000000}, 332332333.333333, "Large Range");
    runTest({1.5, 2.5, 3.5}, 0.666667, "Floating-Point");
    runTest({2, 2, 4, 4}, 1.0, "Duplicates");

    return 0;
}