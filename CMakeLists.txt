cmake_minimum_required(VERSION 3.5.0)
project(EclipseCraft VERSION 0.1.0 LANGUAGES C)

find_package(OpenGL 4.6 REQUIRED)

include(CTest)
enable_testing()

include_directories(vendor/GLFW/include vendor/glad/ vendor/KHR vendor/stb vendor/cglm/include/cglm 
vendor/freetype/include vendor/raygui/src vendor/raylib vendor/vui vendor/vui/backends)

link_directories(vendor/GLFW vendor/stb)

file(GLOB_RECURSE GAME_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/game/src/*.c")
file(GLOB_RECURSE PLATFORM_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/platform/src/*.c")

add_executable(EclipseCraft ${GAME_SOURCES} ${PLATFORM_SOURCES})

target_link_libraries(EclipseCraft glfw3 opengl32)

add_subdirectory(vendor/cglm vendor/Nuklear)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
