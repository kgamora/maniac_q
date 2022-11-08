cmake_minimum_required(VERSION 3.23)
project(maniac_q)

set(CMAKE_CXX_STANDARD 20)

include_directories(src)
include_directories(include)

add_executable( maniac_q
                src/is_valide_state.cpp
                src/move_check.cpp
                src/read_write.cpp
                src/state.cpp
                src/main.cpp )
