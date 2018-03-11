cmake_minimum_required(VERSION 3.8)
project(LinearEquationSystems)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_CXX_FLAGS  -Wall )
set(SOURCE_FILES main.cpp matrix_generator.h slae_solver.h slae_solver.cpp
        Gauss.cpp)
add_executable(solveSystems ${SOURCE_FILES})