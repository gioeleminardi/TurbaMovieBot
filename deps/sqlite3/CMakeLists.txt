cmake_minimum_required(VERSION 3.12)
project(sqlite3 VERSION 3.35.5)

set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/)
include_directories(${INCLUDE_DIR})
set(SRCS ${CMAKE_CURRENT_SOURCE_DIR}/sqlite3.c)
add_library(${PROJECT_NAME} STATIC ${SRCS})
target_include_directories(${PROJECT_NAME} PUBLIC ${INCLUDE_DIR})
