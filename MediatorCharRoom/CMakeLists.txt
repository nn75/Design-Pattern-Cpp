cmake_minimum_required(VERSION 3.15)
project(MediatorCharRoom)

set(CMAKE_CXX_STANDARD 14)

add_executable(MediatorCharRoom main.cpp Person.cpp Person.h ChatRoom.cpp ChatRoom.h)