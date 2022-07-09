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
/*requires requires (std::ostream& os, T x) {
    os << x;
  } // Legal on gcc, but error on clang: Infinte recursion of substitution
*/
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
namespace details {
  template <std::size_t N = 0, bool first = true, typename... Types>
  std::ostream& print_tuple_elements(std::ostream& os, const std::tuple<Types...>& tpl) {
    if constexpr (N < sizeof...(Types)) {
      if constexpr (not first) {
        os << ',';
      }
      os << std::get<N>(tpl);
      print_tuple_elements<N+1,false>(os, tpl);
    }

    return os;
  }
}

template<typename... Types>
std::ostream& operator<<(std::ostream& os, const std::tuple<Types...>& tpl) {
  os << '(';
  details::print_tuple_elements(os, tpl);
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
