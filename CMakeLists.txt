cmake_minimum_required(VERSION 3.20)
project(teste C)

set(CMAKE_C_STANDARD 11)

include_directories(${CMAKE_SOURCE_DIR})

add_executable(teste main.c)

target_link_libraries(teste ${CMAKE_SOURCE_DIR}/lib/lib.a)