cmake_minimum_required(VERSION 3.10)
project(maniac_q)

set(CMAKE_CXX_STANDARD 20)

if (CMAKE_BUILD_TYPE STREQUAL "Release")
    add_compile_options(-Ofast -flto)
endif()


include_directories(src)
include_directories(include)

add_executable( maniac_q
        src/main.cpp
        src/board.cpp
        src/make_fence.cpp
        src/engine.cpp
        src/validation.cpp
        src/read_write.cpp
        src/make_move.cpp
        src/parse_move.cpp
        )
