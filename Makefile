CXX = g++
CXXFLAGS = -std=c++20 -Wall
TARGET = main
SRC = main.cpp
HEADERS = mustUseThisPointer.h std_function.h parse_FIX_zero_copy.h

$(TARGET): $(SRC) $(HEADERS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC) $(LDLIBS)

clean:
	rm -f $(TARGET)

.PHONY: clean