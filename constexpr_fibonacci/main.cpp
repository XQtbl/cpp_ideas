// Made by xqtbl

#include <iostream>
#include <tuple>
#include <utility>
#include <array>

#include "../common/prettify.h"

template <size_t... PrevSeq, size_t SecondPrev, size_t FirstPrev>
consteval std::integer_sequence<size_t, SecondPrev+FirstPrev, FirstPrev, SecondPrev, PrevSeq...>  next_fib(std::integer_sequence<size_t, FirstPrev, SecondPrev, PrevSeq...>) {
    return {};
}

template <size_t... Ints>
consteval auto seq_into_array(std::integer_sequence<size_t, Ints...> s) {
    return std::array<size_t, s.size()>{Ints...};
}

template <size_t N>
consteval auto fib() {
    return next_fib(fib<N-1>());
}

template <>
consteval auto fib<1>() {
    return next_fib(std::integer_sequence<size_t, 1, 0>{});
}

template <>
consteval auto fib<0>() {
    return std::integer_sequence<size_t, 0>{};
}

int main() {
    constexpr size_t max_n = 100;
    auto result = seq_into_array(fib<max_n>());
    std::cout << prettify(result) << '\n';
}
