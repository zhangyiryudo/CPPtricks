
#include <iostream>
#include <atomic>
using namespace std;

void test_compare_exchange() 
{
    std::cout << "--compare_exchange_weak!" << std::endl;

    // Simple example of compare_exchange_weak
    std::atomic<int> x(10);
    int expected = 5;
    int desired = 20;
    
    std::cout << "expected was: " << expected << std::endl;
    // Try to change x from 10 to 20
    bool success = x.compare_exchange_weak(expected, desired);
    
    std::cout << "\n compare_exchange_weak example:" << std::endl;
    std::cout << "Success: " << (success ? "true" : "false") << std::endl;
    std::cout << "x value: " << x.load() << std::endl;
    std::cout << "expected become: " << expected << std::endl;

}