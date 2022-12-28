cmake_minimum_required(VERSION 3.25.1)

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

# Tutorial 1
add_executable(tutorial-1 src/tutorial-1/main.cpp)
target_include_directories(tutorial-1 PUBLIC ${INCLUDES})
target_link_libraries(tutorial-1 ${LIBS})