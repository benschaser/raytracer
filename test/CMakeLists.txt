cmake_minimum_required(VERSION 3.16)
project(raytracer)

add_compile_options(-llvm -Wall -Wextra -pedantic -std=c++17)

add_library(vector3d vector3d.cpp)
add_library(ray ray.cpp)
add_library(object object.cpp)
add_library(pixels pixels.cpp)
add_library(lodepng lodepng.cpp)
add_library(hit hit.cpp)
add_library(world world.cpp)
add_library(camera camera.cpp)
add_library(parser parser.cpp)
add_library(random random.cpp)
add_library(material material.cpp)
add_library(texture texture.cpp)
add_library(BVH_node BVH_node.cpp)
add_library(hitbox hitbox.cpp)
target_link_libraries(ray PUBLIC vector3d)
target_link_libraries(pixels PUBLIC vector3d lodepng)
target_link_libraries(object PUBLIC ray hit)
target_link_libraries(camera PUBLIC vector3d)
target_link_libraries(material PUBLIC hit ray)
target_link_libraries(world PUBLIC BVH_node)
target_link_libraries(object PUBLIC world)

add_executable(raytrace main.cpp)
target_link_libraries(raytrace PUBLIC ray object pixels hit vector3d camera world parser random material texture BVH_node hitbox)

add_executable(threads threading-example.cpp)


