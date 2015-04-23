cmake_minimum_required(VERSION 2.8.4)
project(ThreadPool)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -std=c++11")

set(SOURCE_FILES main.cpp)
add_executable(ThreadPool ${SOURCE_FILES} thread_pool.h thread_pool.cc work.h work.cc delegate.h delegate.cc)
target_link_libraries(ThreadPool pthread)
