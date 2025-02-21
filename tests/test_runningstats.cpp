#define CATCH_CONFIG_MAIN  // Catch2 provides the main() function
#include <catch2/catch_all.hpp>
#include "RunningStats.h"  // Assuming the header is named RunningStats.h
#include <vector>
#include <cmath>
using namespace Catch;

TEST_CASE("RunningStats basic functionality", "[RunningStats]") {
    RunningStats<double> stats;

    SECTION("Initial state") {
        REQUIRE(stats.NumDataValues() == 0);
        REQUIRE(stats.Mean() == Approx(0.0));
        REQUIRE(stats.Variance() == Approx(0.0));
        REQUIRE(stats.StandardDeviation() == Approx(0.0));
        REQUIRE(stats.Skewness() == Approx(0.0));
        REQUIRE(stats.Kurtosis() == Approx(0.0));
    }

    SECTION("Single value") {
        stats.Push(5.0);
        REQUIRE(stats.NumDataValues() == 1);
        REQUIRE(stats.Mean() == Approx(5.0));
        REQUIRE(stats.Variance() == Approx(0.0)); // n < 2, so variance is 0
        REQUIRE(stats.StandardDeviation() == Approx(0.0));
    }

    SECTION("Multiple values") {
        std::vector<double> values = {1.0, 2.0, 3.0, 4.0, 5.0};
        for (double val : values) {
            stats.Push(val);
        }

        REQUIRE(stats.NumDataValues() == 5);
        REQUIRE(stats.Mean() == Approx(3.0)); // (1+2+3+4+5)/5 = 3
        REQUIRE(stats.Variance() == Approx(2.5)); // Sample variance: [(1-3)^2 + (2-3)^2 + ...] / (5-1)
        REQUIRE(stats.StandardDeviation() == Approx(std::sqrt(2.5)));
        REQUIRE(stats.Skewness() == Approx(0.0).epsilon(0.01)); // Should be near 0 for symmetric data
        REQUIRE(stats.Kurtosis() == Approx(-1.3).epsilon(0.1)); // Excess kurtosis for uniform distribution
    }

    SECTION("Clear resets stats") {
        stats.Push(1.0);
        stats.Push(2.0);
        stats.Clear();
        REQUIRE(stats.NumDataValues() == 0);
        REQUIRE(stats.Mean() == Approx(0.0));
        REQUIRE(stats.Variance() == Approx(0.0));
    }

    // SECTION("Confidence interval") {
    //     std::vector<double> values = {1.0, 2.0, 3.0, 4.0};
    //     for (double val : values) {
    //         stats.Push(val);
    //     }
    //     double ci95 = stats.ConfidenceInterval(CI::CI95);
    //     double expected_ci95 = 1.96 * std::sqrt(2.5) / std::sqrt(4.0); // z * σ / √n
    //     REQUIRE(ci95 == Approx(expected_ci95).epsilon(0.01));
    // }
}

TEST_CASE("RunningStats combination", "[RunningStats]") {
    RunningStats<double> stats1;
    RunningStats<double> stats2;

    SECTION("Combining two sets") {
        stats1.Push(1.0);
        stats1.Push(2.0);
        stats2.Push(3.0);
        stats2.Push(4.0);

        RunningStats<double> combined = stats1 + stats2;
        REQUIRE(combined.NumDataValues() == 4);
        REQUIRE(combined.Mean() == Approx(2.5)); // (1+2+3+4)/4
        REQUIRE(combined.Variance() == Approx(5.0 / 3.0)); // [(1-2.5)^2 + ...] / 3
        REQUIRE(combined.StandardDeviation() == Approx(std::sqrt(5.0 / 3.0)));

        // Test += operator
        stats1 += stats2;
        REQUIRE(stats1.NumDataValues() == 4);
        REQUIRE(stats1.Mean() == Approx(2.5));
        REQUIRE(stats1.Variance() == Approx(5.0 / 3.0));
    }

    SECTION("Combining empty and non-empty") {
        stats1.Push(1.0);
        stats1.Push(2.0);
        RunningStats<double> combined = stats1 + stats2; // stats2 is empty
        REQUIRE(combined.NumDataValues() == 2);
        REQUIRE(combined.Mean() == Approx(1.5));
        REQUIRE(combined.Variance() == Approx(0.5));
    }
}