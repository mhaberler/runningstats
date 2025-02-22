#include <iostream>
#include "CircularBuffer.hpp"

int main() {
    CircularBuffer<int> cb(3);
    
    // Pushing elements
    std::cout << "Push 1: " << cb.push(1) << "\n";  // Prints 1 (true)
    std::cout << "Push 2: " << cb.push(2) << "\n";  // Prints 1 (true)
    std::cout << "Push 3: " << cb.push(3) << "\n";  // Prints 1 (true)
    std::cout << "Push 4: " << cb.push(4) << "\n";  // Prints 0 (false, full)
    
    // Popping elements
    int value;
    while (cb.pop(value)) {
        std::cout << "Popped: " << value << "\n";   // Prints 1, 2, 3
    }
    std::cout << "Pop empty: " << cb.pop(value) << "\n";  // Prints 0 (false)
    
    // Using iterators
    cb.push(5);
    cb.push(6);
    std::cout << "Values: ";
    for (int val : cb) {
        std::cout << val << " ";  // Prints 5 6
    }
    std::cout << "\n";

    return 0;
}