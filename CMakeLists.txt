cmake_minimum_required(VERSION 3.5.0)
project(EclipseCraft VERSION 0.1.0 LANGUAGES C)

find_package(OpenGL 4.6 REQUIRED)

include(CTest)
enable_testing()

include_directories(vendor/GLFW/include vendor/glad/ vendor/KHR vendor/stb)
link_directories(vendor/GLFW vendor/stb)

add_executable(EclipseCraft main.c glad.c Buffers.c Shaders.c texture.c)

target_link_libraries(EclipseCraft glfw3 opengl32)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
