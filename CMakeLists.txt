cmake_minimum_required(VERSION 3.20)
project(ProjetoAED)

set(CMAKE_CXX_STANDARD 14)

add_executable(ProjetoAED main.cpp minHeap.h graph.h graph.cpp STCP.cpp STCP.h MainMenu.h MainMenu.cpp TextTable.h)