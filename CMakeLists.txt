cmake_minimum_required(VERSION 3.4.0)

set(PROJECT_NAME tests)

project(${PROJECT_NAME} CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/tests
)

file(GLOB_RECURSE CPP_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/tests/old/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/tests/*.cpp
)
file(GLOB_RECURSE H_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/include/di/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/tests/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/tests/*.hpp
)
set(SOURCE_FILES ${CPP_FILES} ${H_FILES})

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
