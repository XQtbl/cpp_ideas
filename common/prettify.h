#ifndef CPP_IDEAS_PRETTIFY_H
#define CPP_IDEAS_PRETTYFY_H

#include <ranges>
#include <charconv>
#include <ostream>
#include <tuple>
#include <utility>
#include <string_view>
#include <string>

// Forward decls
template<typename... Types>
std::ostream& operator<<(std::ostream&, const std::tuple<Types...>&);
template<typename T, typename U>
std::ostream& operator<<(std::ostream&, const std::pair<T,U>&);

template <typename T>
concept convertible_to_chars = requires (T x) {
  std::to_chars(nullptr, nullptr, x);
};

// Prettify ranges
template <std::ranges::forward_range T>
  requires (not (convertible_to_chars<T> ||
                 std::is_same_v<std::decay_t<T>, std::string> ||
                 std::is_same_v<std::decay_t<T>, std::string_view> ||
                 std::is_same_v<std::decay_t<T>, char*>))
std::ostream& operator<<(std::ostream& os, const T& rng) {
  os << '[';
  for (bool first = true; auto& element : rng) {
    if (first) {
      first = false;
    }
    else {
      os << ',';
    }
    
    os << element;
  }
  os << ']';
  
  return os;
}

// Prettify tuples
template<typename... Types>
std::ostream& operator<<(std::ostream& os, const std::tuple<Types...>& tpl) {
  auto print_elements = [&]() {
    auto inner = [&]<std::size_t N = 0, bool first = true>(const auto self) {
      if constexpr (not (N < sizeof...(Types))) return;
      else {
        if constexpr (not first) {
          os << ',';
        }
        os << std::get<N>(tpl);

        self.template operator()<N+1,false>(self);
      }
    };

    inner.operator()(inner);
  };

  os << '(';
  print_elements();
  os << ')';

  return os;
}

// Prettify pairs
template<typename T, typename U>
std::ostream& operator<<(std::ostream& os, const std::pair<T,U>& p) {
    os << '(' << p.first << ',' << p.second << ')';

    return os;
}
#endif
