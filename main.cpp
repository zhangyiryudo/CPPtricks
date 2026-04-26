#include <iostream>
#include "mustUseThisPointer.h"
#include "std_function.h"
#include "parse_FIX_zero_copy.h"


int main() {
    test_std_function();
    printParsedFIXFields();
    store_lambda_in_vector();
    return 0;
}