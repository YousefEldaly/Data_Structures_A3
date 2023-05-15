cmake_minimum_required(VERSION 3.24)
project(Trees)

set(CMAKE_CXX_STANDARD 17)

add_executable(Trees main.cpp Student.cpp Student.h BST.cpp BST.h AVL.cpp AVL.h)
