#include <ranges>
#include <thread>
#include <vector>
#include <iostream>
#include <algorithm>

#include <prettify.h>
#include "lock_free_stack.h"

template <typename T>
using arr = std::array<T, 256>;

int main() {
    lock_free_stack<int, std::vector> s;
//     lock_free_stack<int, arr> s;
    {
        std::array<std::jthread, 16> threads;
        for (auto &&t: threads) {
            t = std::jthread([](lock_free_stack<int, std::vector> &s) {
                for (auto i : std::views::iota(1) | std::views::take(10)) {
                    s.push(i);
                }
            }, std::ref(s));
        }
    }

    std::cout << "내부 데이터: " << prettify(s.get_container()) << '\n';
    std::cout << "0이 아닌 데이터 갯수: " << std::ranges::count_if(s.get_container(), [](auto& e) {return e != 0;}) << '\n';
    std::cout << "기록된 사이즈: " << s.size() << '\n';

    for (auto i : std::views::iota(1) | std::views::take(10)) {
        std::cout << i << "의 갯수: " << std::ranges::count(s.get_container(), i) << '\n';
    }
}
