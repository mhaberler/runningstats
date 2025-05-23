# collection of online algorithms statistics classes 

## RunningStats, RunningRegression
class encapsulating various online algorithms for basic statistics

Source: https://www.johndcook.com/blog/skewness_kurtosis/

## TimeStats

class for taking timing samples and computing stats on them

subclass of `RunningStats``

works on ESP32 only for now

## ExponentialSmoothing

straight from https://en.wikipedia.org/wiki/Exponential_smoothing#Basic_(simple)_exponential_smoothing

## float vs double, counter type

defaults to float, see "rstypes.h"

to change:
`#define _float_t double`

counters - default to uint32_t

to change:
`#define _counter_t uint64_t`

## further sources

note to self: these might be interesting:

https://github.com/alexander-yu/stream/tree/master?tab=readme-ov-file

https://github.com/onlinestats - histogram, autocorrelation, autocovariance 

https://github.com/pierre/holt-winters/blob/master/holt-winters.c 

https://github.com/topics/online-algorithms

https://github.com/breese/trial.online

https://github.com/breese/trial.circular/blob/develop/doc/circular.adoc
