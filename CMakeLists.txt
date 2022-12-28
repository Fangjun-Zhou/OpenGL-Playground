cmake_minimum_required(VERSION 3.25.1)

project(GLFWOpenGL)

add_executable(${PROJECT_NAME} src/main.cpp)

# GLFW
add_subdirectory(external/glfw)
target_include_directories(${PROJECT_NAME} PUBLIC external/glfw/include)
target_link_libraries(${PROJECT_NAME} glfw)

# GLEW
target_include_directories(${PROJECT_NAME} PUBLIC external/glew/include)
target_link_libraries(${PROJECT_NAME} ${CMAKE_SOURCE_DIR}/external/glew/build/lib/libglew.a)

# GLM
add_subdirectory(external/glm)
target_include_directories(${PROJECT_NAME} PUBLIC external/glm)
target_link_libraries(${PROJECT_NAME} glm)