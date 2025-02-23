#pragma once

#include "RunningVariance.hpp"
#include "CircularBuffer.hpp"


template <typename T>

class WindowVariance : RunningVariance<T> {

//   private:
public: 
    CircularBuffer<T>  *cb;


    WindowVariance(size_t window_size) {
        cb = new CircularBuffer<T>(window_size);
    }
    ~WindowVariance() { delete cb; }
     
    void Add(T x) {
        cb->push(x);
    }

    T Variance()  {
        RunningVariance<T>::Clear();
        for (T value : *cb) {
            RunningVariance<T>::Push(value);
        }
        return RunningVariance<T>::Variance();
    }
    T Mean()  {
        Variance();
        return RunningVariance<T>::Mean();
    }

    size_t getWindowSize() const {
        return cb->capacity();
    }

};
