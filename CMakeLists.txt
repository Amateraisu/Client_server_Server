cmake_minimum_required(VERSION 3.25)
project(Socket)

set(CMAKE_CXX_STANDARD 23)

add_executable(Socket main.cpp)
target_link_libraries(Socket Ws2_32)
