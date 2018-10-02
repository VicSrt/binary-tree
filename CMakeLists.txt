cmake_minimum_required(VERSION 3.9)
project(PROJET C)

set(CMAKE_C_STANDARD 11)

add_executable(PROJET main.c cmake-build-debug/projet.c cmake-build-debug/projet.h)