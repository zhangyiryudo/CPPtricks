#include <iostream>
#include "mustUseThisPointer.h"
#include "std_function.h"
#include "parse_FIX_zero_copy.h"


int main() {
    test_std_function();
    printParsedFIXFields();
    return 0;
}