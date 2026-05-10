//a variadic template to hold a sequence of types.
template<typename... Types>
struct type_list {
    static constexpr size_t size = sizeof...(Types);
};

template <typename List>
struct front;

template <typename T, typename... Ts>
struct front<type_list<T, Ts...>> {
    using type = T;
};

// Helper alias
template <typename List>
using front_t = typename front<List>::type;


template <typename List>
struct pop_front;

template <typename T, typename... Ts>
struct pop_front<type_list<T, Ts...>> {
    using type = type_list<Ts...>;
};

template <typename List>
using pop_front_t = typename pop_front<List>::type;

template <typename List, typename NewT>
struct push_back;

template <typename... Ts, typename NewT>
struct push_back<type_list<Ts...>, NewT> {
    using type = type_list<Ts..., NewT>;
};

template <typename List, typename NewT>
using push_back_t = typename push_back<List, NewT>::type;

#include <type_traits>

void test_my_type_list() {
    // Define a list of types
    using my_types = type_list<int, float, double>;

    // 1. Check size
    static_assert(my_types::size == 3, "Size should be 3");

    // 2. Get the front type
    using first = front_t<my_types>;
    static_assert(std::is_same_v<first, int>, "First type should be int");

    // 3. Remove the front type
    using remaining = pop_front_t<my_types>; // Result: type_list<float, double>
    static_assert(remaining::size == 2, "Remaining size should be 2");

    // 4. Add a type
    using extended = push_back_t<my_types, char>; // Result: type_list<int, float, double, char>
    static_assert(extended::size == 4, "Extended size should be 4");
}