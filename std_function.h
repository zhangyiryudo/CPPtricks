#include <iostream>
#include <functional>
using namespace std;

int add(int a, int b) { return a + b; }

struct Calculator {
    int offset = 10;
    int addOffset(int x) { return x + offset; }
};

void test_std_function() {
    // A wrapper that takes two ints and returns an int
    std::function<int(int, int)> op;
    op = add;                    // Pointing to a free function
    std::cout << op(10, 5) <<endl;      // 15

    //A. Lambdas (Capture and No-Capture)
    int multiplier = 3;
    std::function<int(int)> multiply = [multiplier](int x) { return x * multiplier;  };
    std::cout << multiply(10) << std::endl; // 30

    //C. Member Functions
    Calculator calc;
    std::function<int(int)> addOffsetFunc = [&calc](int x) { return calc.addOffset(x); };
    std::cout << addOffsetFunc(22) << std::endl; // 22 + 10 = 32
}


//store C++ lambdas in a std::vector
// Instead, you must use std::function to provide a type-erased wrapper that can hold any callable object
void store_lambda_in_vector() {
    // A vector that stores functions taking an int and returning void
    std::vector<std::function<void(int)>> tasks;

    // Adding lambdas to the vector
    tasks.push_back([](int x) { 
        std::cout << "Task 1: Square is " << x * x << std::endl; 
    });
    tasks.push_back([](int x) { 
        std::cout << "Task 2: Doubled is " << x * 2 << std::endl; 
    });

    // Executing the lambdas
    for (const auto& task : tasks) {
        task(5);
    }
}