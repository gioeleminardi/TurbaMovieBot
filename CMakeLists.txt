cmake_minimum_required(VERSION 3.17)
project(TurbaMovieBot)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/deps/sqlite_orm)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/deps/tgbot-cpp)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

file(GLOB_RECURSE SRCS src/*.cpp)

add_executable(${PROJECT_NAME} ${SRCS})
target_link_libraries(${PROJECT_NAME} TgBot sqlite_orm ${CMAKE_DL_LIBS})
