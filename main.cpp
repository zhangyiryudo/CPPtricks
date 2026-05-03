#include <iostream>
#include "mustUseThisPointer.h"
#include "std_function.h"
#include "parse_FIX_zero_copy.h"
#include "string_SSO.h"
#include "StableVector.h"
#include "my_vector_SVO.h"
#include "all_string_comp.h"
#include "StringCurrencySSO.h"
#include "atomic_usage.h"
using namespace std;

int main() {
    test_compare_exchange();
}

// int main() {
//     // test_std_function();
//     // printParsedFIXFields();
//     // store_lambda_in_vector();

//     std::cout << sizeof(std::string) << std::endl; // 32 on my system, due to SSO optimization
//     std::cout << sizeof(bool) << std::endl; // 1 on my system

//     SSOString s1("Hello, World!"); // Short string, should use local buffer
//     SSOString s2("This is a much longer string that exceeds the SSO capacity."); // Long string, should use heap allocation
//     std::cout << "s1: " << s1.c_str() << " (size: " << s1.size() << ", is_local: " << s1.is_local() << ")" << std::endl;
//     std::cout << "s2: " << s2.c_str() << " (size: " << s2.size() << ", is_local: " << s2.is_local() << ")" << std::endl;


//     SsoSimpleString s3("Short string"); // Should use short buffer
//     SsoSimpleString s4("This is a longer string that will use the long buffer"); // Should use long buffer
//     std::cout << "s3: " << s3.c_str() << " (size: " << s3.size() << ", is_long: " << s3.is_long_string() << ")" << std::endl;
//     std::cout << "s4: " << s4.c_str() << " (size: " << s4.size() << ", is_long: " << s4.is_long_string() << ")" << std::endl;

//     cout << "sizeof(SSOString): " << sizeof(SSOString) << endl; // 24 bytes due to SSO optimization
//     cout << "sizeof(SsoSimpleString): " << sizeof(SsoSimpleString) << endl; // 32 bytes

//     StableVector<int> stableVec;
//     stableVec.push_back(5);
//     stableVec.push_back(10);
//     std::cout << "Element at index 0: " << stableVec[0] << std::endl;
//     std::cout << "Element at index 1: " << stableVec[1] << std::endl;
//     return 0;
// }

