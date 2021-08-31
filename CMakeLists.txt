cmake_minimum_required(VERSION 3.17)
project(Regex_Automata C)

set(CMAKE_C_STANDARD 99)

add_executable(Regex_Automata main.c regex.c regex.h)