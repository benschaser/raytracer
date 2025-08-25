cmake_minimum_required(VERSION 3.20)
project(raytracer)

add_compile_options(-Wall -pedantic -std=c++17)

file(GLOB_RECURSE ENGINE_SOURCES src/engine/src/*.cpp)


add_library(engine STATIC ${ENGINE_SOURCES})
target_include_directories(engine PUBLIC src/engine/include)

add_executable(raytracer src/main.cpp)
target_link_libraries(raytracer PUBLIC engine)

#Copy Test Files
add_custom_command(TARGET raytracer POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/test $<TARGET_FILE_DIR:raytracer>/test
    COMMENT "Copying test folder to build directory"
)