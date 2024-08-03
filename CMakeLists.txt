cmake_minimum_required(VERSION 3.5)

project(abiba VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "-pedantic-errors -ggdb -Wall -Wextra -Werror -Wshadow")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g3 -fsanitize=thread")
 
set(PROJECT_SOURCES
        src/main.cpp
        src/pool.cpp
        include/pool.hpp
        include/runner.hpp
)

add_executable(abiba
    ${PROJECT_SOURCES}
)

target_include_directories(abiba PRIVATE include)