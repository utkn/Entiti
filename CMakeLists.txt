cmake_minimum_required(VERSION 3.5)
project(Entiti)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp src/BaseSystem.cpp include/BaseSystem.h include/Component.h include/Entiti.h src/Handle.cpp include/Handle.h src/Manager.cpp include/Manager.h src/Misc.cpp include/Misc.h include/System.h)
add_library(Entiti ${SOURCE_FILES})