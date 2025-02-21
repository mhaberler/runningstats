# Paths for Homebrew-installed Catch2
CATCH2_INCLUDE = /opt/homebrew/Cellar/catch2/$(shell brew list --versions catch2 | tail -1 | cut -d' ' -f2)/include
CATCH2_LIB = /opt/homebrew/Cellar/catch2/$(shell brew list --versions catch2 | tail -1 | cut -d' ' -f2)/lib


# Compiler settings
CXX = clang++
#CXX = c++
CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic -I..
LDFLAGS = /opt/homebrew/Cellar/catch2/3.8.0/lib/libCatch2.a /opt/homebrew/Cellar/catch2/3.8.0/lib/libCatch2Main.a

# Source and target
TEST_SRC = test_runningstats.cpp
TEST_TARGET = test_runningstats

# Default target
all: $(TEST_TARGET)

# Link and compile the test executable
$(TEST_TARGET): $(TEST_SRC) ../RunningStats.h
	$(CXX) $(CXXFLAGS) -I$(CATCH2_INCLUDE) $(TEST_SRC) -o $(TEST_TARGET) $(LDFLAGS)

# Run the tests
test: $(TEST_TARGET)
	./$(TEST_TARGET)

# Clean up
clean:
	rm -f $(TEST_TARGET)

# Phony targets
.PHONY: all test clean