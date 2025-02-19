#ifndef RUNNINGSTATS_H
#define RUNNINGSTATS_H
// from: https://www.johndcook.com/blog/skewness_kurtosis/

#include "rstypes.h"

typedef enum {
  CI90=0,
  CI95,
  CI99,
} ci_t;

class RunningStats {
public:
  RunningStats();
  void Clear();
  void Push(_float_t x);
  _counter_t NumDataValues() const;
  _float_t Mean() const;
  _float_t Variance() const;
  _float_t PopulationVariance() const; 
  _float_t StandardDeviation() const;
  _float_t Skewness() const;
  _float_t Kurtosis() const;
  _float_t ConfidenceInterval(ci_t ci);

  friend RunningStats operator+( RunningStats const &a,  RunningStats const &b);
  RunningStats &operator+=(const RunningStats &rhs);

private:
  _counter_t n;
  _float_t M1, M2, M3, M4;
};

#endif
