# Running Statistics

A collection of efficient online (streaming) algorithms for statistical calculations in C++ and TypeScript. Compute statistics incrementally without storing all data points in memory.

## Table of Contents

- [Features](#features)
- [Available Classes](#available-classes)
- [Installation](#installation)
  - [C++ (Arduino/PlatformIO)](#c-arduinoplatformio)
  - [TypeScript/JavaScript](#typescriptjavascript)
- [Quick Start](#quick-start)
- [Class Reference](#class-reference)
- [Building and Testing](#building-and-testing)
- [Configuration](#configuration)
- [References](#references)

## Features

- **Memory Efficient**: Compute statistics without storing all data points
- **Real-time**: Update statistics incrementally as new data arrives
- **Dual Implementation**: Identical APIs in C++ and TypeScript
- **Numerically Stable**: Uses robust algorithms (Welford, rolling variance, etc.)
- **Template-based C++**: Configurable precision (float/double) and counter types
- **Comprehensive**: Mean, variance, skewness, kurtosis, regression, smoothing, and more

## Available Classes

### Core Statistics
- **`RunningVariance`** - Running mean and variance (Welford's algorithm)
- **`RunningStats`** - Complete statistics: mean, variance, skewness, kurtosis, confidence intervals
- **`RollingVariance`** - Variance over a fixed-size sliding window (efficient rolling algorithm)
- **`WindowVariance`** - Sliding window variance using circular buffer

### Smoothing and Filtering
- **`ExponentialSmoothing`** - Exponential weighted moving average (EWMA)
- **`ExponentialWeightedVariance`** - Exponentially weighted moving variance (EWMV)

### Regression and Fitting
- **`RunningRegression`** - Online linear regression with correlation and prediction
- **`QuadraticFitOnline`** - Online quadratic curve fitting using recursive least squares

### Utilities
- **`CircularBuffer`** - Efficient fixed-size circular buffer
- **`TimerStats`** - Timing statistics (ESP32 only)
- **`RateStats`** - Rate/frequency calculation

## Installation

### C++ (Arduino/PlatformIO)

**PlatformIO:**
```ini
[env:myenv]
lib_deps =
    ; Add to your platformio.ini
```

**Arduino IDE:**
Copy all `.hpp` and `.cpp` files to your project folder.

**Manual Include:**
```cpp
#include "RunningStats.hpp"
#include "ExponentialWeightedVariance.hpp"
// Include other headers as needed
```

### TypeScript/JavaScript

**NPM:**
```bash
cd js/
npm install
npm run build
```

**Import:**
```typescript
import {
    RunningStats,
    ExponentialWeightedVariance,
    QuadraticFitOnline,
    // ... other classes
} from './index';
```

## Quick Start

### C++ Example

```cpp
#include "RunningStats.hpp"
#include "ExponentialWeightedVariance.hpp"

int main() {
    // Running statistics
    RunningStats<double> stats;
    stats.Push(1.5);
    stats.Push(2.3);
    stats.Push(1.8);

    std::cout << "Mean: " << stats.Mean() << std::endl;
    std::cout << "StdDev: " << stats.StandardDeviation() << std::endl;

    // Exponentially weighted variance
    ExponentialWeightedVariance<double> ewv(0.1); // alpha = 0.1
    ewv.Push(10.0);
    ewv.Push(12.0);
    ewv.Push(11.5);

    std::cout << "EWMA Mean: " << ewv.Mean() << std::endl;
    std::cout << "EWMV: " << ewv.Variance() << std::endl;

    return 0;
}
```

### TypeScript Example

```typescript
import { RunningStats, ExponentialWeightedVariance } from './index';

// Running statistics
const stats = new RunningStats();
stats.push(1.5);
stats.push(2.3);
stats.push(1.8);

console.log(`Mean: ${stats.mean()}`);
console.log(`StdDev: ${stats.standardDeviation()}`);

// Exponentially weighted variance
const ewv = new ExponentialWeightedVariance(0.1); // alpha = 0.1
ewv.push(10.0);
ewv.push(12.0);
ewv.push(11.5);

console.log(`EWMA Mean: ${ewv.mean()}`);
console.log(`EWMV: ${ewv.variance()}`);
```

## Class Reference

### RunningStats / RunningVariance

Calculate comprehensive running statistics using Welford's online algorithm.

**Source:** [John D. Cook's Blog](https://www.johndcook.com/blog/skewness_kurtosis/)

**Methods:**
- `Push(x)` / `push(x)` - Add a data point
- `Mean()` / `mean()` - Get mean
- `Variance()` / `variance()` - Get sample variance
- `StandardDeviation()` / `standardDeviation()` - Get standard deviation
- `Skewness()` / `skewness()` - Get skewness (RunningStats only)
- `Kurtosis()` / `kurtosis()` - Get kurtosis (RunningStats only)

### ExponentialSmoothing

Exponential smoothing filter for time series data.

**Source:** [Wikipedia - Exponential Smoothing](https://en.wikipedia.org/wiki/Exponential_smoothing#Basic_(simple)_exponential_smoothing)

**Methods:**
- `Push(x)` / `push(x)` - Add value and update
- `Value()` / `getValue()` - Get smoothed value
- `setAlpha(alpha)` - Set smoothing factor (0 < alpha ≤ 1)

### ExponentialWeightedVariance

Exponentially weighted moving variance with decaying weights on historical data.

**Source:** [Grok EWMV Derivation](https://grok.com/share/bGVnYWN5_86b4d8af-96c7-40f3-9de2-cc1b0e9d975c)

**Methods:**
- `Push(x)` / `push(x)` - Add data point
- `Mean()` / `mean()` - Get exponentially weighted mean
- `Variance()` / `variance()` - Get exponentially weighted variance
- `setAlpha(alpha)` - Set decay factor (higher alpha = more recent weight)

### QuadraticFitOnline

Online quadratic curve fitting using recursive least squares.

**Source:** [Grok Quadratic Fit](https://grok.com/share/bGVnYWN5_7e91020c-652b-4ec1-ba92-9f6ceacd7440)

**Methods:**
- `update(x, y)` - Add (x, y) data point
- `getCoefficients()` - Returns [c, b, a] for y = ax² + bx + c
- `predict(x)` - Predict y for given x
- `calculateRSquared(data)` - Calculate fit quality

### TimerStats

Statistics on timing measurements (ESP32 only).

Subclass of `RunningStats` with ESP32-specific microsecond timing.

### RollingVariance

Efficient variance calculation over a fixed-size sliding window.

**Source:** [StackOverflow - Rolling Variance](https://stackoverflow.com/questions/5147378/rolling-variance-algorithm/74239458#74239458)

**Methods:**
- `Push(x)` / `push(x)` - Add value to window
- `Variance()` / `variance()` - Get variance of current window
- `Mean()` / `mean()` - Get mean of current window

## Building and Testing

### C++ Tests

```bash
cd tests/
make              # Build all tests
make test         # Build and run all tests
make clean        # Clean build artifacts

# Run individual tests
make test_exponentialweightedvariance
make run-exponentialweightedvariance
```

### TypeScript Tests

```bash
cd js/
npm install       # Install dependencies
npm test          # Run Jest tests
npm run build     # Build TypeScript to dist/
npm run dev       # Watch mode for development
```

## Configuration

### C++ Type Configuration

Customize floating-point precision and counter types in `rstypes.h` or before including headers:

```cpp
// Use double precision instead of float (default)
#define _float_t double

// Use 64-bit counters instead of 32-bit (default)
#define _counter_t uint64_t

#include "RunningStats.hpp"
```

### Template Parameters

```cpp
// Explicit type specification
RunningVariance<double, uint64_t> stats;
ExponentialWeightedVariance<float> ewv(0.1);
```

## References

### Algorithm Sources
- [John D. Cook - Running Statistics](https://www.johndcook.com/blog/skewness_kurtosis/)
- [Wikipedia - Exponential Smoothing](https://en.wikipedia.org/wiki/Exponential_smoothing)
- [Wikipedia - Welford's Algorithm](https://en.wikipedia.org/wiki/Algorithms_for_calculating_variance#Welford's_online_algorithm)
- [StackOverflow - Rolling Variance Algorithm](https://stackoverflow.com/questions/5147378/rolling-variance-algorithm/74239458#74239458)
- [Grok - Exponentially Weighted Moving Variance](https://grok.com/share/bGVnYWN5_86b4d8af-96c7-40f3-9de2-cc1b0e9d975c)
- [Grok - Online Quadratic Fitting](https://grok.com/share/bGVnYWN5_7e91020c-652b-4ec1-ba92-9f6ceacd7440)

### Further Reading
- [alexander-yu/stream](https://github.com/alexander-yu/stream) - Stream processing library
- [onlinestats](https://github.com/onlinestats) - Histogram, autocorrelation, autocovariance
- [Holt-Winters Implementation](https://github.com/pierre/holt-winters/blob/master/holt-winters.c)
- [trial.online](https://github.com/breese/trial.online) - Online algorithms
- [trial.circular](https://github.com/breese/trial.circular/blob/develop/doc/circular.adoc) - Circular buffers

## License

MIT
