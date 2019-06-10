cmake_minimum_required(VERSION 3.4.0)

set(PROJECT_NAME tests)

project(${PROJECT_NAME} CXX)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/.
    ${CMAKE_CURRENT_SOURCE_DIR}/../include
)

file (GLOB CPP_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
)
file (GLOB H_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/*.hpp
)
set (SOURCE_FILES ${CPP_FILES} ${H_FILES})

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
