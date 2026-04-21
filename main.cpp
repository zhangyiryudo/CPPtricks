#include <iostream>
#include "mustUseThisPointer.h"
#include "std_function.h"
using namespace std;

int main() {
    // A wrapper that takes two ints and returns an int
    std::function<int(int, int)> op;
    op = add;                    // Pointing to a free function
    std::cout << op(10, 5) <<endl;      // 15

    //A. Lambdas (Capture and No-Capture)
    int multiplier = 3;
    std::function<int(int)> multiply = [multiplier](int x) { return x * multiplier;  };

    //C. Member Functions
    Calculator calc;
    std::function<int(int)> addOffsetFunc = [&calc](int x) { return calc.addOffset(x); };
}