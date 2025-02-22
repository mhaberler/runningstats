#include <iostream>
#include "CircularBuffer.hpp"

int main() {
    CircularBuffer<int> cb(3);
    
    // Push elements (will overwrite when full)
    cb.push(1);
    cb.push(2);
    cb.push(3);
    std::cout << "After 3 pushes, size: " << cb.size() << "\n";  // Prints 3
    
    cb.push(4);  // Overwrites 1
    std::cout << "After 4th push, size: " << cb.size() << "\n";  // Still 3
    
    // Print all elements
    std::cout << "Values: ";
    for (int val : cb) {
        std::cout << val << " ";  // Prints 2 3 4
    }
    std::cout << "\n";
    
    // Pop elements
    int value;
    while (cb.pop(value)) {
        std::cout << "Popped: " << value << "\n";  // Prints 2, 3, 4
    }
    
    // Push more after empty
    cb.push(5);
    cb.push(6);
    std::cout << "New values: ";
    for (int val : cb) {
        std::cout << val << " ";  // Prints 5 6
    }
    std::cout << "\n";

    return 0;
}