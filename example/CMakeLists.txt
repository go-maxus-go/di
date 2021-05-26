cmake_minimum_required(VERSION 3.4.0)

set(PROJECT_NAME example)

project(${PROJECT_NAME} CXX)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/.
    ${CMAKE_CURRENT_SOURCE_DIR}/../include
)

file(GLOB CPP_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Model/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Model/Impl/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Logic/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Logic/Impl/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/App/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/App/Impl/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Util/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Util/Impl/*.cpp
)
file(GLOB H_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Model/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Model/Impl/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Logic/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Logic/Impl/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/App/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/App/Impl/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Util/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Util/Impl/*.h
)
set(SOURCE_FILES ${CPP_FILES} ${H_FILES})

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
