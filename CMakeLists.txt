cmake_minimum_required(VERSION 2.8)
project(KD_Tree)

set(CMAKE_CXX_COMPILER, g++)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES source/main.cpp
                 source/kdtree_node.h
                 source/kdtree_node.cpp
                 source/kdtree.h
                 source/kdtree.cpp
                 source/kdtree_constants.h
                 source/kdtree_constants.cpp)

add_executable(kd_trees.prod.tsk ${SOURCE_FILES})