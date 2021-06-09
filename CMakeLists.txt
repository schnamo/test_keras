cmake_minimum_required(VERSION 3.19)
project(test_keras)

set(CMAKE_CXX_STANDARD 14)

add_executable(test_keras main.cpp SequenceToProfile.cpp SequenceToProfile.h)

find_package(frugally-deep CONFIG REQUIRED)
target_link_libraries(test_keras PRIVATE frugally-deep::fdeep)