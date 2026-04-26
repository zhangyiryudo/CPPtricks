#include <iostream>
#include "mustUseThisPointer.h"
#include "std_function.h"
#include "parse_FIX_zero_copy.h"
#include "string_SSO.h"


int main() {
    test_std_function();
    printParsedFIXFields();
    store_lambda_in_vector();

    std::cout << sizeof(std::string) << std::endl; // 32 on my system, due to SSO optimization
    std::cout << sizeof(bool) << std::endl; // 1 on my system

    SSOString s1("Hello, World!"); // Short string, should use local buffer
    SSOString s2("This is a much longer string that exceeds the SSO capacity."); // Long string, should use heap allocation
    std::cout << "s1: " << s1.c_str() << " (size: " << s1.size() << ", is_local: " << s1.is_local() << ")" << std::endl;
    std::cout << "s2: " << s2.c_str() << " (size: " << s2.size() << ", is_local: " << s2.is_local() << ")" << std::endl;

    return 0;
}