cmake_minimum_required(VERSION 3.12)
project(Task1)

set(CMAKE_CXX_STANDARD 11)

add_executable(Task1 src/Main.cpp src/Restaurant.cpp src/Dish.cpp src/Table.cpp src/Customer.cpp src/Action.cpp)