#include <prettify.h>
#include <vector>
#include <utility>
#include <tuple>
#include <unordered_set>
#include <iostream>
#include <string>
#include <string_view>

int main() {
    std::cout << std::vector{4,2,1} << '\n';
    std::cout << std::unordered_set{"Hello", "Hi", "Hi"} << '\n';

    auto s1 = std::string{"Hello"};
    auto sv1 = std::string_view{s1.begin(), s1.begin() + 4};

    std::cout << sv1 << '\n';
}