cmake_minimum_required(VERSION 3.10)
project(CHIP-8)

set(CMAKE_CXX_STANDARD 17)

# set(SDL2_DIR "${CMAKE_SOURCE_DIR}/dependencies/SDL")

add_subdirectory(dependencies/SDL)

add_executable(CHIP-8 source/main.cpp)

target_include_directories(CHIP-8 PRIVATE dependencies/SDL/include)

target_compile_definitions(CHIP-8 PRIVATE SDL_MAIN_HANDLED)

# add_definitions(-DSDL_MAIN_HANDLED)

#link_directories(${SDL2_DIR}/lib)


target_link_libraries(CHIP-8 PRIVATE SDL2-static)


