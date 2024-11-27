cmake_minimum_required(VERSION 3.22)
project(ayed_treesort_cpp)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)

add_executable(ayed_treesort_cpp
        main.cpp
        src/treesort.cpp
        
)