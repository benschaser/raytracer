cmake_minimum_required(VERSION 3.20)
project(raytracer)

add_compile_options(-Wall -Wextra -pedantic -std=c++17)

file(GLOB_RECURSE ENGINE_SOURCES src/engine/src/*.cpp)


add_library(engine STATIC ${ENGINE_SOURCES})
target_include_directories(engine PUBLIC src/engine/include)

add_executable(main src/main.cpp)
target_link_libraries(main PUBLIC engine)

