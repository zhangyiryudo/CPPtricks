//Millenium
#pragma once
// please implement a custom container template with similar semantics
// to std::vector but with a twist that first N elements are stored in
// the object itself rather than on the heap (similar to small string
// optimization). feel free to utilize STL containers, there's no need
// to implement allocations yourself

// the starting point below already has class and function declaration
// and tests, it just needs implementation

#include <iostream>
#include <assert.h>
//for production-grade Small Vector Optimization (like folly::small_vector or llvm::SmallVector):
//T m_local[N]; array approach requires T to be default-constructible
template <typename T, size_t N>
class my_vector {
public:
    my_vector() : m_size(0) {}
    size_t size() const { return m_size; }

    void push_back(const T& value) {
        m_size++;
        if (m_size < N) {
            m_local[m_size] = value; // If T has deleted its assignment operator, this will fail.
        } else {
            m_heap.push_back(value); // Store in heap vector
        }
    }

    T& operator[](size_t index) {
        if (index < N) {
            return m_local[index];
        } else {
            return m_heap[index - N];
        }
    }

private:
    T m_local[N]; // Local storage for the first N elements
    std::vector<T> m_heap; // Heap storage for elements beyond N
    size_t m_size; // Total number of elements in the vector
};

//In a strict low-latency environment, a true SVO avoids this by using an uninitialized memory buffer 
//(e.g., alignas(T) std::byte m_local[N * sizeof(T)]) and relies on placement new inside the push_back method to 
// construct objects only when they are actually added, and explicitly calls destructors when they are removed.
#include <type_traits>
#include <new> // Required for placement new

template <typename T, size_t N>
class my_vector_svo {
private:
    size_t m_size;
    // 1. Create a raw buffer with correct size and alignment
    alignas(T) unsigned char m_buffer[N * sizeof(T)]; 
    std::vector<T> m_heap;

public:
    my_vector_svo() : m_size(0) {}
    size_t size() const { return m_size; }

    void push_back(const T& value) {
        if (m_size < N) {
            // 2. Use placement new to construct T directly into the buffer
            // This does NOT require T to be default-constructible
            // new ( &((T*)m_buffer)[m_size] ) T(value);
            new (m_buffer + m_size * sizeof(T)) T(value); // Alternative syntax
        } else {
            m_heap.push_back(value);
        }
        m_size++;
    }

    T& operator[](size_t index) {
        if (index < N) {
            // 3. Cast the buffer to the correct type
            return ((T*)m_buffer)[index];
        }
        return m_heap[index - N];
    }

    // 4. CRITICAL: You must manually call destructors for the local buffer!
    ~my_vector_svo() {
        size_t local_count = (m_size < N) ? m_size : N;
        for (size_t i = 0; i < local_count; ++i) {
            ((T*)m_buffer)[i].~T();
        }
    }
};