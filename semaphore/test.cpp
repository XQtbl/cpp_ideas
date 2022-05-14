#include <iostream>
#include <syncstream>
#include <thread>
#include <atomic>
#include <array>

// compare_exchange_weak is excuted like
bool cmpxchg(int& self, int& x1, int x2) {
    if (self == x1) {
        self = x2;
        return true;
    }
    else {
        x1 = self;
        return false;
    }
}

void use_semaphore(std::atomic<int>& semaphore, int& cnt) {
    auto id = std::this_thread::get_id();
    int expect = 0;
    while (expect = 0, !semaphore.compare_exchange_weak(expect, 1, std::memory_order_relaxed));

    {
        std::osyncstream sout{std::cout};
        sout << "Unlocked in " << id << '\n';
    }

    for (auto i = 0; i < 100000; i++) ++cnt;

    semaphore.store(0, std::memory_order_relaxed);
}

void dont_use_semaphore(int& cnt) {
    for (auto i = 0; i < 100000; i++) ++cnt;
}

int main() {
    std::atomic<int> semaphore{1};
    int cnt = 0;

    {
        std::array<std::jthread, 64> threads;
        for (auto &&t: threads) {
            t = std::jthread{use_semaphore, std::ref(semaphore), std::ref(cnt)};
//        t = std::thread{dont_use_semaphore, std::ref(cnt)};
        }

        semaphore.store(0, std::memory_order_relaxed);
    }

    {
        std::osyncstream sout{std::cout};
        sout << "End: " << cnt << '\n';
    }

    return 0;
}
