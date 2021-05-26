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
    ${CMAKE_CURRENT_SOURCE_DIR}/App/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/App/Impl/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Car/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Car/Impl/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Gas/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Gas/Impl/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Brake/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Brake/Impl/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Util/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Util/Impl/*.cpp
)
file(GLOB H_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/App/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/App/Impl/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Car/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Car/Impl/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Gas/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Gas/Impl/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Brake/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Brake/Impl/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Util/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Util/Impl/*.h
)
set(SOURCE_FILES ${CPP_FILES} ${H_FILES})

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
