cmake_minimum_required(VERSION 3.10)
project(GL_TEST)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

include_directories(GL_TEST "${PROJECT_SOURCE_DIR}/include" "${OPENGL_INCLUDE_DIR}" "~/libs/glfw-3.2.1/include/GLFW")

set(SOURCE main.cpp src/glad.c)
add_executable(GL_TEST ${SOURCE})

target_link_libraries(GL_TEST ${OPENGL_gl_LIBRARY} glfw ${CMAKE_DL_LIBS})
