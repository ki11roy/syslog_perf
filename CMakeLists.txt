cmake_minimum_required(VERSION 2.8.9)
project (syslog_perf)

set (CMAKE_CXX_STANDARD 11)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

add_definitions(-Wall)
add_definitions(-Wextra)
add_definitions(-pedantic)
add_executable(syslog_perf syslog_perf.cc)

