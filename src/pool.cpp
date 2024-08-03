#include "pool.hpp"
#include <iostream>

ThreadPool::ThreadPool() {
    const unsigned int THREAD_NUMBER =
        std::max(1U, std::thread::hardware_concurrency());
    all_threads.reserve(THREAD_NUMBER);
}

void ThreadPool::start() {
    for (std::size_t i = 0; i < all_threads.capacity(); ++i) {
        all_threads.emplace_back(&ThreadPool::run, this);
    }
    std::cout << "Started\n";
}

void ThreadPool::run() {
    while (!quite) {
        std::unique_lock lock(mutex_for_queue);
        cond_var_for_threads.wait(lock, [this]() -> bool {
            return !tasks.empty() || quite;
        });

        if (quite) {
            lock.unlock();
            break;
        }


        Runner task = std::move(tasks.front());
        tasks.pop();
        lock.unlock();

        task.execute();
    }
}

void ThreadPool::add_task(const Runner &task) {
    std::unique_lock lock(mutex_for_queue);
    tasks.push(task);
    lock.unlock();

    cond_var_for_threads.notify_one();
}

void ThreadPool::shutdown() {
    quite = true;
    cond_var_for_threads.notify_all();
}

ThreadPool::~ThreadPool() {
    shutdown();

    for (std::size_t i = 0; i < all_threads.size(); ++i) {
        all_threads[i].join();
    }
}