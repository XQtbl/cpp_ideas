#include <prettify.h>
#include <vector>
#include <utility>
#include <tuple>
#include <unordered_set>
#include <iostream>
#include <string>
#include <string_view>
#include <map>

int main() {
    using namespace std::literals::string_view_literals;

    std::cout << std::string("Testing") << '\n';
    std::cout << std::vector{4,2,1} << '\n';
    std::cout << std::unordered_set{"Hello"sv, "Hi"sv, "Hi"sv} << '\n';
    std::cout << std::make_pair(3.4, 1.2) << '\n';
    std::cout << std::map<int, std::string>{{1, "Hi"}, {2, "XQtbl"}} << '\n';
    std::cout << std::make_tuple(1,4,2) << '\n';
    std::cout << std::vector(3, std::tuple(1,4,2)) << '\n';
}