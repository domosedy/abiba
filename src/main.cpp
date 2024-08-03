#include <iostream>
#include "pool.hpp"

int main() {
    ThreadPool pool;
    pool.start();

    for (unsigned int i = 0; i < 1e4; ++i) {
        pool.add_task(Runner{"main.cpp", 1, i});
    }

    std::this_thread::sleep_for(10000ms);
    std::cout << "Done\n";
    return 0;
}
