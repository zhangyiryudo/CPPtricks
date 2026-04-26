// in std::vector, when we do push_back, all the iterators are invalidated, and we need to reassign them.
// class StableVector will not invalidate existing iterators when we do push_back
#include <iostream>
#include <vector>
using namespace std;
//The best way to solve this is to use a Segmented Vector (an array of fixed-size chunks).
// template<typename T>
// class StableVector {
//     static constexpr std::size_t CHUNK_SIZE = 256;
// public:
//     void push_back(const T& ele) {
//         if (chunks.empty() || chunks.back().size() >= CHUNK_SIZE) {
//             chunks.emplace_back();
//             chunks.back().reserve(CHUNK_SIZE); // CRITICAL: Prevent inner reallocation
//         }
//         chunks.back().push_back(ele); // Add element to the last chunk
//     }

//     T& operator[](size_t index) {
//         size_t chunk_index = index / CHUNK_SIZE;
//         size_t within_chunk_index = index % CHUNK_SIZE;
//         return chunks[chunk_index][within_chunk_index];
//     }

// private:
//     std::vector<std::vector<T>> chunks; // Vector of chunks
// };

// The Better Fix: std::unique_ptr<T[]>
// While the std::vector<std::vector<T>> fix works, it's not the most efficient way to build a segmented vector. 
// Every inner std::vector carries the overhead of three pointers (begin, end, and capacity) and manages its own size, 
// which you don't really need since your chunks are fixed-size.
// A more standard and memory-efficient way to implement this is using raw arrays managed by smart pointers:
#include <memory>

template<typename T>
class StableVector {
    static constexpr std::size_t CHUNK_SIZE = 256;
    
public:
    void push_back(const T& ele) {
        // If we are at exactly a chunk boundary, allocate a new chunk
        if (m_size % CHUNK_SIZE == 0) {
            chunks.push_back(make_unique<T[]>(CHUNK_SIZE));
            // chunks.push_back(new T[CHUNK_SIZE]);
        }
        
        // Calculate where the element goes and place it
        size_t chunk_index = m_size / CHUNK_SIZE;
        size_t within_chunk = m_size % CHUNK_SIZE;
        
        chunks[chunk_index][within_chunk] = ele;
        m_size++;
    }

    T& operator[](size_t index) {
        return chunks[index / CHUNK_SIZE][index % CHUNK_SIZE];
    }
    
    size_t size() const { return m_size; }

private:
    std::vector<unique_ptr<T[]>> chunks; 
    // std::vector<T*> chunks; 
    size_t m_size = 0; // We have to track total size manually now
};