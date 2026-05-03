#include <string>

void printStringInfo() {
    std::cout << "sizeof(std::string_view): " << sizeof(std::string_view) << std::endl;
    // std::string_view is 16 bytes, which typically consists of a pointer to the string data and a size (length) field.
    std::cout << "sizeof(std::string): " << sizeof(std::string) << std::endl;
    // std::string is 32 bytes on my system, which includes the small string optimization (SSO) buffer and other metadata.
    std::cout << "sizeof(char[7]): " << sizeof(const char[7]) << std::endl;
    std::cout << "sizeof(const char*): " << sizeof(const char*) << std::endl;

// 1. std::string str1 = "Hello"; (The Owning Container)
// // Memory/Allocation: this involves dynamic memory allocation on the heap.Small String Optimization (SSO). The string data will be stored directly inside the std::string object's internal buffer on the stack
// 2. std::string_view str2 = "Hello"; (The Non-Owning View)
// // Memory/Allocation: this does not involve any memory allocation. It simply holds a pointer to the string literal "Hello" and its length, stored in a read-only section of memory.
// 3. const char * str3 = "Hello"; 
// //(The Read-Only Pointer)Memory/Allocation: a single pointer on the stack. The string literal "Hello" is stored in a read-only section of memory, and str3 points to it.
// 4. char str4[6] = "Hello"; 
// //Memory/Allocation: This allocates a 6-byte array directly on the stack. 
// // At runtime (or optimized at compile time), 
}