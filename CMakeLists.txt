cmake_minimum_required(VERSION 3.5.0)
project(EclipseCraft VERSION 0.1.0 LANGUAGES C)

find_package(OpenGL 4.6 REQUIRED)

include(CTest)
enable_testing()

include_directories(vendor/GLFW/include vendor/glad/ vendor/KHR vendor/stb vendor/cglm/include/cglm 
vendor/freetype/include vendor/raygui/src vendor/raylib vendor/vui vendor/vui/backends)

link_directories(vendor/GLFW vendor/stb)

add_executable(EclipseCraft main.c glad.c Buffers.c Shaders.c texture.c debug.c voxel.c)

target_link_libraries(EclipseCraft glfw3 opengl32)

add_subdirectory(vendor/cglm vendor/Nuklear)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/frag.txt DESTINATION ${CMAKE_BINARY_DIR}/Debug)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/vertex.txt DESTINATION ${CMAKE_BINARY_DIR}/Debug)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
