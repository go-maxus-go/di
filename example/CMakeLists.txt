cmake_minimum_required(VERSION 3.4.0)

set(PROJECT_NAME example)

project(${PROJECT_NAME} CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/.
    ${CMAKE_CURRENT_SOURCE_DIR}/../include
)

file(GLOB CPP_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Client/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Services/*.cpp
)
file(GLOB H_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/Client/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Services/*.h
)
set(SOURCE_FILES ${CPP_FILES} ${H_FILES})

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
