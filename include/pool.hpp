#ifndef POOL_HPP_
#define POOL_HPP_

#include <atomic>
#include <condition_variable>
#include <memory>
#include <mutex>
#include <queue>
#include <thread>
#include <vector>
#include "runner.hpp"

class ThreadPool {
    std::vector<std::thread> all_threads{};
    std::queue<Runner> tasks{};

    std::mutex mutex_for_queue;
    std::condition_variable cond_var_for_threads;

    std::atomic<bool> quite{false};

    void run();

public:
    ThreadPool();

    ThreadPool(const ThreadPool &) = delete;
    ThreadPool(ThreadPool &&) = delete;

    ThreadPool &operator=(const ThreadPool &) = delete;
    ThreadPool &operator=(ThreadPool &&) = delete;

    ~ThreadPool();

    void start();
    void add_task(const Runner &task);
    void shutdown();
};

#endif  // POOL_HPP_