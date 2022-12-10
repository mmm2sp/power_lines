cmake_minimum_required(VERSION 3.3)
project(Power_lines)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

set(CMAKE_CXX_STANDARD 17)

set(PROGRAM_SRCS
        include/src/main.cpp
        include/src/calculate.cpp
        )

include_directories(
        include/
)

add_executable(Power_lines ${PROGRAM_SRCS})

target_link_libraries(Power_lines ${OPENGL_LIBRARIES})
target_link_libraries(Power_lines ${GLUT_LIBRARIES})
target_link_libraries(Power_lines -lopengl32 -g -lfreeglut)