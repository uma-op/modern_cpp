cmake_minimum_required(VERSION 3.15)

project(imdb)

set(CXX_STANDARD 17)
set(CXX_STANDARD_REQUIRED True)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

file(GLOB SOURCES "${SOURCE_DIR}/*.cpp")

find_package(Boost COMPONENTS program_options REQUIRED)

add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} Boost::program_options)
target_include_directories(${PROJECT_NAME} PUBLIC ${INCLUDE_DIR})

