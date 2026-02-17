# Makefile for running statistics tests
# Usage:
#   make              - Build all tests
#   make test         - Build and run all tests
#   make clean        - Remove all built executables
#   make <testname>   - Build a specific test

CXX = g++
CXXFLAGS = -std=c++17 -Wall -I..
PARENT_DIR = ..

# Test executables
TESTS = test_circularbuffer \
        test_windowvariance \
        test_exponentialweightedvariance \
        rvtest \
        variancetest

# Default target: build all tests
all: $(TESTS)

# Individual test targets

# CircularBuffer test (header-only)
test_circularbuffer: test_circularbuffer.cpp $(PARENT_DIR)/CircularBuffer.hpp
	$(CXX) $(CXXFLAGS) test_circularbuffer.cpp -o test_circularbuffer

# WindowVariance test (header-only)
test_windowvariance: test_windowvariance.cpp $(PARENT_DIR)/WindowVariance.hpp $(PARENT_DIR)/CircularBuffer.hpp $(PARENT_DIR)/RunningVariance.hpp
	$(CXX) $(CXXFLAGS) test_windowvariance.cpp -o test_windowvariance

# ExponentialWeightedVariance test (header-only)
test_exponentialweightedvariance: test_exponentialweightedvariance.cpp $(PARENT_DIR)/ExponentialWeightedVariance.hpp
	$(CXX) $(CXXFLAGS) test_exponentialweightedvariance.cpp -o test_exponentialweightedvariance

# RollingVariance test (header-only)
rvtest: rvtest.cpp $(PARENT_DIR)/RollingVariance.hpp
	$(CXX) $(CXXFLAGS) rvtest.cpp -o rvtest

# Variance test (needs RunningStats.cpp)
variancetest: variancetest.cpp $(PARENT_DIR)/RunningStats.cpp $(PARENT_DIR)/RunningStats.hpp $(PARENT_DIR)/RollingVariance.hpp
	$(CXX) $(CXXFLAGS) variancetest.cpp $(PARENT_DIR)/RunningStats.cpp -o variancetest

# Build and run all tests
test: all
	@echo "========================================="
	@echo "Running all tests..."
	@echo "========================================="
	@echo ""
	@echo "--- test_circularbuffer ---"
	@./test_circularbuffer
	@echo ""
	@echo "--- test_windowvariance ---"
	@./test_windowvariance
	@echo ""
	@echo "--- test_exponentialweightedvariance ---"
	@./test_exponentialweightedvariance
	@echo ""
	@echo "--- rvtest ---"
	@./rvtest
	@echo ""
	@echo "--- variancetest ---"
	@./variancetest
	@echo ""
	@echo "========================================="
	@echo "All tests completed!"
	@echo "========================================="

# Clean up built executables
clean:
	rm -f $(TESTS)

# Run individual tests
run-circularbuffer: test_circularbuffer
	./test_circularbuffer

run-windowvariance: test_windowvariance
	./test_windowvariance

run-exponentialweightedvariance: test_exponentialweightedvariance
	./test_exponentialweightedvariance

run-rvtest: rvtest
	./rvtest

run-variancetest: variancetest
	./variancetest

.PHONY: all test clean run-circularbuffer run-windowvariance run-exponentialweightedvariance run-rvtest run-variancetest
