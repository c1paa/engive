cmake_minimum_required(VERSION 3.31)
project(engive_v1)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(src/libs/glfw)

set(ASSIMP_DIR ${CMAKE_SOURCE_DIR}/src/libs/assimp)
set(ASSIMP_INCLUDE_DIR ${ASSIMP_DIR}/include)
set(ASSIMP_LIB ${ASSIMP_DIR}/libassimp.6.0.2.dylib)

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

target_link_libraries(engive_v1 glfw ${ASSIMP_LIB})

if (APPLE)
    target_link_libraries(engive_v1 "-framework OpenGL")
else()
    target_link_libraries(engive_v1 GL)
endif()


add_custom_command(TARGET engive_v1 POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${ASSIMP_LIB}
        $<TARGET_FILE_DIR:engive_v1>
)