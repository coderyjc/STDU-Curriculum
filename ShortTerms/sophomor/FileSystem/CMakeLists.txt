cmake_minimum_required(VERSION 3.19)
project(FileSystem)

set(CMAKE_CXX_STANDARD 14)

add_executable(FileSystem main.cpp classes/MemoryNode.cpp classes/MemoryNode.h)