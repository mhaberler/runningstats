#ifndef RUNNINGREGRESSION
#define RUNNINGREGRESSION

// from: https://www.johndcook.com/blog/running_regression/

#include "RunningStats.hpp"

class RunningRegression {
public:
  RunningRegression();
  void Clear();
  void Push(_float_t x, _float_t y);
  long long NumDataValues() const;
  _float_t Slope() const;
  _float_t Intercept() const;
  _float_t Correlation() const;

  friend RunningRegression operator+(const RunningRegression a,
                                     const RunningRegression b);
  RunningRegression &operator+=(const RunningRegression &rhs);

private:
  RunningStats x_stats;
  RunningStats y_stats;
  _float_t S_xy;
  long long n;
};

#endif
