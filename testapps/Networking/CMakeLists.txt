cmake_minimum_required(VERSION 2.8)
project(networking)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -ggdb -O0")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O2")

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fpic")
set(CMAKE_CXX_STANDARD 11)

include_directories(include)

link_libraries("${PROJECT_NAME}" pthread rt)

add_executable(networking
               src/networking/MulticastClient.cpp
               src/networking/IGMPListener.cpp
               src/rtpstream/RTPStreaming.cpp
               main.cpp include/Logging.h include/FileReader.h src/filesystem/FileReader.cpp include/TSPacket.h include/RTPHeader.h src/networking/RTPHeader.cpp)
