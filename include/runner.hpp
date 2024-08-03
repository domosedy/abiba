#ifndef RUNNER_HPP_
#define RUNNER_HPP_

#include <iostream>
#include <string>
#include <thread>

using namespace std::chrono_literals;

class Runner {
    const std::string file_to_run;
    const unsigned int task_number;
    const unsigned int test_number;

public:
    Runner(
        const std::string &file,
        const unsigned int task,
        const unsigned int test
    )
        : file_to_run(file), task_number(task), test_number(test) {
    }

    bool execute() {
        std::cout << "Running task " << task_number << " with test "
                  << test_number << " on file " << file_to_run << " in thread "
                  << std::this_thread::get_id() << std::endl;
        std::this_thread::sleep_for(20ms);
        return true;
    }
};

#endif  // RUNNER_HPP_