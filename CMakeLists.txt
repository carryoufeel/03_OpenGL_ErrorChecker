cmake_minimum_required(VERSION 3.12)

project(OpenGL_Project)

set(CMAKE_CXX_STANDARD 17)

include_directories(SYSTEM ${CMAKE_CURRENT_SOURCE_DIR}/thirdParty/include)

link_directories(SYSTEM ${CMAKE_CURRENT_SOURCE_DIR}/thirdParty/lib)


add_executable(openglStudy "main.cpp" "glad.c")

target_link_libraries(openglStudy glfw3.lib)