//
// Created by xqtbl on 22. 5. 14.
//

#ifndef CPP20_LEARNING_PRETTIFY_H
#define CPP20_LEARNING_PRETTIFY_H
#include <ranges>
#include <string>
#include <sstream>

template <std::ranges::input_range T>
std::string prettify(T&& data) {
    auto ss = std::ostringstream{};

    ss << '[';

    for (auto first = true; auto&& element : data) {
        if (first) [[unlikely]] first = false;
        else [[likely]] ss << ", ";

        ss << element;
    }

    ss << ']';

    return ss.str();
}
#endif //CPP20_LEARNING_PRETTIFY_H
