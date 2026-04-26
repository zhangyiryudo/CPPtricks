//SSO: avoid expensive heap allocations for short strings.
//Normally, a string class needs three pointers (or equivalent size_t types) to manage heap memory:
//a pointer to the data, the size of the string, and the capacity of the allocated buffer. 
//On a 64-bit system, this totals 24 bytes.
#include <cstring>

class SSOString {
private:
    // On a 64-bit system:
    // char* (8 bytes) + size_t (8 bytes) + size_t (8 bytes) = 24 bytes.
    // We can use 23 bytes for characters, leaving 1 byte for the flag/size.
    static const size_t SSO_CAPACITY = 23;

    union {
        // Layout 1: Used when the string is long (stored on the heap)
        struct {
            char* ptr;
            size_t size;
            size_t capacity;
        } heap;

        // Layout 2: Used when the string is short (stored locally)
        struct {
            char buffer[SSO_CAPACITY];
            unsigned char length_and_flag; 
        } local;
    } data;

public:
    SSOString(const char* str) {
        size_t len = strlen(str);
        if (len <= SSO_CAPACITY) {
            // Use local storage
            memcpy(data.local.buffer, str, len);
            data.local.buffer[len] = '\0'; // Null-terminate
            data.local.length_and_flag = len; // High bit remains 0, Store length and flag in one byte
            // cout << "is_local() : " << is_local() << endl;
        } else {
            // Use heap storage
            data.heap.ptr = new char[len + 1];
            // cout << "Allocating heap memory for string: " << str << endl;
            memcpy(data.heap.ptr, str, len);
            data.heap.ptr[len] = '\0'; // Null-terminate
            data.heap.size = len;
            data.heap.capacity = len + 1;
            data.local.length_and_flag = 0x80; // Set the high bit to indicate heap storage
            // cout << "is_local() : " << is_local() << endl;
        }
    }

    ~SSOString() {
        if (!is_local()) {
            delete[] data.heap.ptr;
        }
    }

    // Helper to check if we are currently using the local buffer.
    // We use the highest bit of the last byte as a flag.
    // If the bit is 0, it's local. If it's 1, it's on the heap.
    bool is_local() const {
        return (data.local.length_and_flag & 0x80) == 0;
    }

    size_t size() const {
        return is_local() ? (data.local.length_and_flag & 0x7F) : data.heap.size; // Mask out the flag bit
    }

    const char* c_str() const {
        return is_local() ? data.local.buffer : data.heap.ptr;
    }
};