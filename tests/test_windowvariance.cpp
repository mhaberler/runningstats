#include <iostream>
#include "WindowVariance.hpp"

int main() {
    WindowVariance<float> winvar(3);
    
    // Adding elements
    winvar.Add(1);
    winvar.Add(2);
    winvar.Add(3);
    
    // iterate
    for (float val : *winvar.cb) {
        std::cout << val << "\n";  // Prints 5 6
    }
    std::cout <<  "add 4\n";  // Prints 5 6

    winvar.Add(4);

    for (float val : *winvar.cb) {
        std::cout << val << "\n";  // Prints 5 6
    }
    
    std::cout << "Variance:" << winvar.Variance() << "\n";  
    std::cout << "Mean:" << winvar.Mean() << "\n";  

    winvar.Add(7);
    std::cout << "Variance:" << winvar.Variance() << "\n";  
    std::cout << "Mean:" << winvar.Mean() << "\n";  

    return 0;
}