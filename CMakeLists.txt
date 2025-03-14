cmake_minimum_required(VERSION 3.10)

project (CHIP-8)


set(SDL2_DIR "${CMAKE_SOURCE_DIR}/dependencies/SDL")
set(SOURCE_DIR "${CMAKE_SOURCE_DIR}/source")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -mconsole")

include_directories(${SDL2_DIR}/include)
include_directories(${SOURCE_DIR})

link_directories(${SDL2_DIR}/lib)

ADD_LIBRARY(LibsModule STATIC
    ${SOURCE_DIR}/chip8.cpp
    ${SOURCE_DIR}/chip8.h
    ${SOURCE_DIR}/main.cpp
)

target_link_libraries(LibsModule SDL2 SDL2main)


add_executable(CHIP-8 ${SOURCE_DIR}/main.cpp)

target_link_libraries(CHIP-8 LibsModule SDL2 SDL2main)
