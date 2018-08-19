cmake_minimum_required(VERSION 3.12)
project(CA_lab C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -lgraph")

#SET(GCC_COVERAGE_LINK_FLAGS    "-lgraph")
#SET(GCC_COVERAGE_LINK_FLAGS    "-lm")
#set(CMAKE_C_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}" )
set(GCC_COVERAGE_COMPILE_FLAGS "-Wall -Wextra -Wconversion")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}" )

add_executable(CA_lab main.c utility.h constant.h)