cmake_minimum_required(VERSION 3.17)
project(ZAPOCET)

set(CMAKE_CXX_STANDARD 20)

add_executable(ZAPOCET main.cpp BigNum.cpp BigNum.h BugNumException.h)