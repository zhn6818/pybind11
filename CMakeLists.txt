cmake_minimum_required(VERSION 3.14)
project(my_project)

cmake_policy(SET CMP0148 NEW)

find_package(Python REQUIRED COMPONENTS Interpreter Development)

find_package(pybind11 REQUIRED)

add_executable(my_app main.cpp)
target_link_libraries(my_app PRIVATE pybind11::module ${Python_LIBRARIES})