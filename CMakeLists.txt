cmake_minimum_required(VERSION 3.17)
project(training)

set(CMAKE_CXX_STANDARD 17)

add_executable(training main.cpp testapps/C++17/StructureBinding.h testapps/crackingCodingInterview/Trees.h testapps/crackingCodingInterview/LinkList.h testapps/C++17/lambdas.h testapps/crackingCodingInterview/Graphs.h testapps/Finance/Primitives.h testapps/Networking/RTPStreaming.h testapps/Networking/include/MulticastClient.h testapps/Networking/src/networking/MulticastClient.cpp testapps/Finance/Numerics.h testapps/Finance/STLAlgorithms.h testapps/Finance/Threading.h)