cmake_minimum_required(VERSION 3.31)
project(engive_v1)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(src/libs/glfw)

include_directories(
        src/libs/glad/include
        src/libs/glfw/include
        src/libs/glm
)

add_executable(engive_v1
        src/main.cpp
        src/render/input.cpp
        src/libs/glad/src/glad.c
)

target_link_libraries(engive_v1 glfw)

if (APPLE)
    target_link_libraries(engive_v1 "-framework OpenGL")
else()
    target_link_libraries(engive_v1 GL)
endif()
