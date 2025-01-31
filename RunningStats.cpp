#include "RunningStats.hpp"
#include <math.h>

// https://www.geeksforgeeks.org/confidence-interval/
// assumes standard distribution
// 90% 1.645
// 95% 1.960
// 99% 2.576
static _float_t z_values[] = {1.645, 1.960, 2.576};

RunningStats::RunningStats() { Clear(); }

void RunningStats::Clear() {
  n = 0;
  M1 = M2 = M3 = M4 = 0.0;
}

void RunningStats::Push(_float_t x) {
  _float_t delta, delta_n, delta_n2, term1;

  long long n1 = n;
  n++;
  delta = x - M1;
  delta_n = delta / n;
  delta_n2 = delta_n * delta_n;
  term1 = delta * delta_n * n1;
  M1 += delta_n;
  M4 += term1 * delta_n2 * (n * n - 3 * n + 3) + 6 * delta_n2 * M2 -
        4 * delta_n * M3;
  M3 += term1 * delta_n * (n - 2) - 3 * delta_n * M2;
  M2 += term1;
}

long long RunningStats::NumDataValues() const { return n; }

_float_t RunningStats::Mean() const { return M1; }

_float_t RunningStats::Variance() const { return M2 / (n - 1.0); }

_float_t RunningStats::StandardDeviation() const { return sqrt(Variance()); }

_float_t RunningStats::Skewness() const {
  return sqrt(_float_t(n)) * M3 / pow(M2, 1.5);
}

_float_t RunningStats::Kurtosis() const {
  return _float_t(n) * M4 / (M2 * M2) - 3.0;
}

_float_t RunningStats::ConfidenceInterval(ci_t ci) {
  // if (n < 300)
  //   return NAN;
  // if (ci < CI90 || ci > CI99)
  //   return NAN;
  return z_values[ci] * StandardDeviation() / sqrt((_float_t)n);
}

RunningStats operator+( RunningStats const &a,  RunningStats const &b) {
  RunningStats combined;

  combined.n = a.n + b.n;

  _float_t delta = b.M1 - a.M1;
  _float_t delta2 = delta * delta;
  _float_t delta3 = delta * delta2;
  _float_t delta4 = delta2 * delta2;

  combined.M1 = (a.n * a.M1 + b.n * b.M1) / combined.n;

  combined.M2 = a.M2 + b.M2 + delta2 * a.n * b.n / combined.n;

  combined.M3 = a.M3 + b.M3 +
                delta3 * a.n * b.n * (a.n - b.n) / (combined.n * combined.n);
  combined.M3 += 3.0 * delta * (a.n * b.M2 - b.n * a.M2) / combined.n;

  combined.M4 = a.M4 + b.M4 +
                delta4 * a.n * b.n * (a.n * a.n - a.n * b.n + b.n * b.n) /
                    (combined.n * combined.n * combined.n);
  combined.M4 += 6.0 * delta2 * (a.n * a.n * b.M2 + b.n * b.n * a.M2) /
                     (combined.n * combined.n) +
                 4.0 * delta * (a.n * b.M3 - b.n * a.M3) / combined.n;

  return combined;
}

RunningStats &RunningStats::operator+=(const RunningStats &rhs) {
  RunningStats combined = *this + rhs;
  *this = combined;
  return *this;
}