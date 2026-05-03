//"Fast & Flexible"
//By using char code[4], you keep the data entirely on the stack and ensure the struct size is exactly 4 bytes.

struct BetterCurrency {
    char code[4]; // 3 characters + null terminator
    // bool operator==(const BetterCurrency& other) const {
    //     // Compare the 4 bytes as a single integer for efficiency
    //     return reinterpret_cast<const uint32_t&>(code) == reinterpret_cast<const uint32_t&>(other.code);
    // }
    constexpr bool operator==(const BetterCurrency& other) const {
        // Compare the 4 bytes as a single integer for efficiency
        // return *reinterpret_cast<const uint32_t*>(code) == *reinterpret_cast<const uint32_t*>(other.code);

        //the reinterpret_cast is not allowed in a constexpr context. Instead, we can compare the bytes directly.
        //Unlike reinterpret_cast, std::bit_cast is explicitly designed to be constexpr.
        return std::bit_cast<uint32_t>(code) == std::bit_cast<uint32_t>(other.code);

        //C++23 features, std::begin_lifetime_as
    }
};