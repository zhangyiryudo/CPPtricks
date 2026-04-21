#include <iostream>
#include <functional>

int add(int a, int b) { return a + b; }

struct Calculator {
    int offset = 10;
    int addOffset(int x) { return x + offset; }
};