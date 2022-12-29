cmake_minimum_required(VERSION 3.25.1)

# Generate compile commands.
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(GLFWOpenGL)

# Include list.
set(INCLUDES "")
# Library list.
set(LIBS "")

# GLFW
add_subdirectory(external/glfw)
list(APPEND INCLUDES external/glfw/include)
list(APPEND LIBS glfw)

# GLEW
add_subdirectory(external/glew/build/cmake)
list(APPEND INCLUDES external/glew/include)
list(APPEND LIBS glew_s)

# GLM
add_subdirectory(external/glm)
list(APPEND INCLUDES external/glm)
list(APPEND LIBS glm)

# Common library
add_library(common src/common/loadShader.cpp src/common/loadShader.hpp)
target_include_directories(common PUBLIC ${INCLUDES})
target_link_libraries(common ${LIBS})
list(APPEND INCLUDES src/common)
list(APPEND LIBS common)

# Tutorial 1
add_executable(tutorial-1 src/tutorial-1/main.cpp)
target_include_directories(tutorial-1 PUBLIC ${INCLUDES})
target_link_libraries(tutorial-1 ${LIBS})

# Tutorial 2
add_executable(tutorial-2 src/tutorial-2/main.cpp src/common/loadShader.cpp)
target_include_directories(tutorial-2 PUBLIC ${INCLUDES})
target_link_libraries(tutorial-2 ${LIBS})