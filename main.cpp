#include <iostream>
#include "mustUseThisPointer.h"
using namespace std;

int main() {
    std::cout << "--main()" << std::endl;
    Derived<int> d;
    d.bar();

    Builder().append("Hello, ").append("world!");
    MyScanner<char>().run();

    return 0;
}