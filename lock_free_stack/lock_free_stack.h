//
// Created by xqtbl on 22. 5. 14.
//

#ifndef CPP20_LEARNING_LOCK_FREE_STACK_H
#define CPP20_LEARNING_LOCK_FREE_STACK_H
#include <ranges>
#include <atomic>
#include <mutex>

template <typename T, template <typename...> typename Container, typename... ContArgs>
requires std::ranges::random_access_range<Container<T, ContArgs...>>
class lock_free_stack {
public:
    using container_type = Container<T, ContArgs...>;
    using value_type = typename container_type::value_type;
    using size_type = typename container_type::size_type;
    using reference = typename container_type::reference;
    using const_reference = typename container_type::const_reference;

    lock_free_stack() : next_index{0}, container{} {}
    void push(value_type val) requires requires (container_type c, size_t s) { c.resize(s); } {
        static std::mutex resize{};

        auto now_idx = next_index.fetch_add(1);
        while (container.capacity() < now_idx + 1) {
            std::lock_guard<std::mutex> lg{resize};
            if (container.capacity() >= now_idx + 1) break;
            container.resize((now_idx + 1) * 2);
        }
        container.begin()[now_idx] = val;
    }
    void push(value_type val) {
        auto now_idx = next_index.fetch_add(1);
        container[now_idx] = val;
    }
    void pop() {
        next_index.fetch_sub(1);
    }
    [[nodiscard]] const_reference top() const {
        return container[next_index.load()-1];
    }
    [[nodiscard]] bool empty() const {
        return next_index.load(std::memory_order_relaxed) == 0;
    }
    [[nodiscard]] size_type size() const {
        return next_index.load(std::memory_order_relaxed);
    }
    [[nodiscard]] const container_type& get_container() const {
        return container;
    }
private:
    std::atomic<size_t> next_index;
    Container<T, ContArgs...> container;
};
#endif //CPP20_LEARNING_LOCK_FREE_STACK_H
