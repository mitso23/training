cmake_minimum_required(VERSION 2.8)
project(rtpserver)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -ggdb -O0")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O2")

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fpic")
set(CMAKE_CXX_STANDARD 11)

include_directories(src)

link_libraries("${PROJECT_NAME}" pthread rt)

add_executable(rtpserver
        src/multicastserver.cpp
        src/multicastserver.hpp
        src/rtpserver.cpp
        src/server.cpp
        src/server.hpp
        src/unicastserver.cpp
        src/unicastserver.hpp
        src/retserver.cpp
        src/retserver.hpp
        src/tsanalyser.cpp
        src/tsanalyser.hpp)
