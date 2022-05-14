//
// Created by xqtbl on 22. 5. 14.
//

#ifndef CPP20_LEARNING_CURRYING_H
#define CPP20_LEARNING_CURRYING_H
template <typename T>
struct curry_result {
    constexpr curry_result(T val): value{val} {}
    constexpr operator T() {
        return value;
    }
    constexpr auto operator()()  {
        return *this;
    }

    T value;
};

template <typename Func, typename ...Args>
constexpr auto curry(Func f, Args... args) {
    if constexpr (requires {f(args...);}) {
        return curry_result{f(args...)};
    }
    else {
        return [=]<typename ...NewArgs>(NewArgs ...new_args) {
            return curry(f, args..., new_args...);
        };
    }
}
template <template <typename...> typename TFunc, typename ...Inner, typename ...Args>
constexpr auto curry(TFunc<Inner...> f, Args... args) {
    if constexpr (requires {f(args...);}) {
        return curry_result{f(args...)};
    }
    else {
        return [=]<typename ...NewArgs>(NewArgs ...new_args) {
            return curry(f, args..., new_args...);
        };
    }
}
#endif //CPP20_LEARNING_CURRYING_H
