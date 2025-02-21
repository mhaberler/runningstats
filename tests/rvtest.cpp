#include <iostream>
#include "RollingVariance.hpp"

int main() {
    RollingVariance<double> rv(5); 
    rv.Push(3.0);
    rv.Push(3.0);
    rv.Push(3.0);
    rv.Push(3.0);
    rv.Push(3.0);
    std::cout << "Mean: " << rv.Mean() << "\n";     // Should be 3.0
    std::cout << "Variance: " << rv.Variance() << "\n"; // Should be 0

    rv.Clear();
    rv.Push(-2);
    rv.Push(-1);
    rv.Push(0);
    rv.Push(1);
    rv.Push(2);
    std::cout << "Mean: " << rv.Mean() << "\n";     // Should be 0
    std::cout << "Variance: " << rv.Variance() << "\n"; // Should be 2.0


    RollingVariance<float> rv_float(2); // Using float
    rv_float.Push(4.5f);
    rv_float.Push(5.5f);
    std::cout << "Mean: " << rv_float.Mean() << "\n";     // Should be 5.0
    std::cout << "Variance: " << rv_float.Variance() << "\n"; // Should be 0.25

    return 0;
}
