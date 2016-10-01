cmake_minimum_required(VERSION 2.8.12)
project(JohnnyRenderer2)

set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -std=c++0x")
set(CMAKE_INCLUDE_CURRENT_DIR ON)

include_directories(${PROJECT_SOURCE_DIR}/src ${PROJECT_SOURCE_DIR}/ext)

add_subdirectory(src)
add_subdirectory(test)

file(GLOB_RECURSE RESOURCES "res/*")
MESSAGE(WARNING ${CMAKE_BINARY_DIR})
file(COPY ${RESOURCES} DESTINATION ${CMAKE_BINARY_DIR}/res)
