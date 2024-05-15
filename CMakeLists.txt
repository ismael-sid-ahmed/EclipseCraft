cmake_minimum_required(VERSION 3.5.0)
project(SchizophreniaCraft VERSION 0.1.0 LANGUAGES C)

find_package(OpenGL 4.6 REQUIRED)

include(CTest)
enable_testing()

include_directories(vendor/GLFW/include vendor/glad/ vendor/KHR)
link_directories(vendor/GLFW)

add_executable(SchizophreniaCraft main.c glad.c Buffers.c Shaders.c)

target_link_libraries(SchizophreniaCraft glfw3 opengl32)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
