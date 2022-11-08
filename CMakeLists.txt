cmake_minimum_required(VERSION 3.23)
project(maniac_q)

set(CMAKE_CXX_STANDARD 14)

include_directories(src)

add_executable(maniac_q
        src/is_valide_state.cpp
        src/move_check.cpp
        src/read_write.cpp
        src/read_write.hpp
        src/state.cpp src/main.cpp)
