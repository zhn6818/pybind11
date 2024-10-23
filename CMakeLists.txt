cmake_minimum_required(VERSION 3.10)
project(CppPythonIntegrationDemo)

# Set C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_BUILD_TYPE Debug)

add_definitions(-O0 -g)

# Find Python libraries (specify Anaconda environment explicitly)
set(Python3_EXECUTABLE /root/anaconda3/envs/pytorch/bin/python)
find_package(Python3 REQUIRED COMPONENTS Interpreter Development)
# find_package(Python3 REQUIRED COMPONENTS Interpreter Development)

# Include Pybind11 (specify Pybind11 explicitly if installed locally)
set(pybind11_DIR /root/anaconda3/envs/pytorch/lib/python3.8/site-packages/pybind11/share/cmake/pybind11)
find_package(pybind11 REQUIRED)

message(STATUS "Python3_EXECUTABLE: ${Python3_EXECUTABLE}")
message(STATUS "Python3_INCLUDE_DIRS: ${Python3_INCLUDE_DIRS}")
message(STATUS "Python3_LIBRARIES: ${Python3_LIBRARIES}")

message("pybind11_INCLUDE_DIRS")
message(${pybind11_INCLUDE_DIRS})
message("Python3_INCLUDE_DIRS")
message(${Python3_INCLUDE_DIRS})
# Include Pybind11 headers
include_directories(${pybind11_INCLUDE_DIRS})


# Set the source file
set(SOURCE_FILE main.cpp)

# Add the executable
add_executable(CppPythonIntegrationDemo ${SOURCE_FILE})

# Link against Python and Pybind11
target_link_libraries(CppPythonIntegrationDemo PRIVATE pybind11::module Python3::Python)

# Include directories for Python headers
include_directories(${Python3_INCLUDE_DIRS})