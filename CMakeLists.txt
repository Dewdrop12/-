cmake_minimum_required(VERSION 3.1.0)

project(calculator
  VERSION 1.0
  LANGUAGES C CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED On)

add_executable(calculator
	calculator.cpp
)