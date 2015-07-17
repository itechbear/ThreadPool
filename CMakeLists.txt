cmake_minimum_required(VERSION 2.8.4)
project(ThreadPool)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -std=c++11")

include_directories(src)

set(SOURCE_FILES src/main.cpp)
add_executable(ThreadPool ${SOURCE_FILES} src/utils/threading/thread_pool.h src/utils/threading/thread_pool.cc src/utils/threading/work.h src/utils/threading/work.cc src/utils/threading/delegate.h src/utils/threading/delegate.cc)
target_link_libraries(ThreadPool pthread tcmalloc)
