cmake_minimum_required(VERSION 3.29)
project(shooter)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(libs/raylib)

add_executable(shooter src/main.cpp
        src/Renderer.cpp
        src/Renderer.h
        src/Game.cpp
        src/Game.h
        src/ECS/EntityManager.cpp
        src/ECS/EntityManager.h
        src/ECS/ComponentArray.h
        src/ECS/ComponentManager.h
        src/ECS/Registry.cpp
        src/ECS/Registry.h)

target_link_libraries(shooter PRIVATE raylib)

target_include_directories(shooter PRIVATE libs/raylib)