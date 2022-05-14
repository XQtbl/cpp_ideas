//
// Created by xqtbl on 22. 5. 14.
//
#include <iostream>
#include <syncstream>
#include <ranges>

#include "currying.h"

template <std::integral... I>
std::integral auto sum(I... xs) {
    return (xs + ...);
}

int main() {
    auto summing1 = curry(sum<int, int, int, int>); // sum: (int, int, int, int) -> int
    auto summing2 = summing1(1);                    // summing1: int -> int -> int -> int -> int
    auto summing3 = summing2(3)(4);                 // summing2: int -> int -> int -> int
    auto summing4 = summing3()(2)();                // summing3: int -> int
                                                    // summing4: int

    std::cout << summing4()()() << '\n';

//    auto print = curry([](std::ostream& os, auto&& out) {os << out;});
//    auto print_with_cout = print(std::osyncstream{std::cout});
//    print_with_cout(10);
//  TODO: Make curry() runnable with type which don't have copy-assignment-operator nor copy-constructor
}