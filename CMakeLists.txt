cmake_minimum_required(VERSION 3.25.1)

# Set C++ standard to C++ 17
set(CMAKE_CXX_STANDARD 17)
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

# ImGui
# Add ImGui source code.
set(IMGUI_SRC "")
set(IMGUI_SRC_DIR external/imgui)
set(IMGUI_INCLUDES "")

list(APPEND IMGUI_SRC ${IMGUI_SRC_DIR}/imgui.cpp)
list(APPEND IMGUI_SRC ${IMGUI_SRC_DIR}/imgui_demo.cpp)
list(APPEND IMGUI_SRC ${IMGUI_SRC_DIR}/imgui_draw.cpp)
list(APPEND IMGUI_SRC ${IMGUI_SRC_DIR}/imgui_tables.cpp)
list(APPEND IMGUI_SRC ${IMGUI_SRC_DIR}/imgui_widgets.cpp)
list(APPEND IMGUI_SRC ${IMGUI_SRC_DIR}/backends/imgui_impl_glfw.cpp)
list(APPEND IMGUI_SRC ${IMGUI_SRC_DIR}/backends/imgui_impl_opengl3.cpp)

list(APPEND IMGUI_INCLUDES ${IMGUI_SRC_DIR})
list(APPEND IMGUI_INCLUDES ${IMGUI_SRC_DIR}/backends)

add_library(imgui STATIC ${IMGUI_SRC})
target_include_directories(
    imgui
    PUBLIC ${IMGUI_INCLUDES}
    PUBLIC external/glfw/include
)
target_link_libraries(imgui glfw)

list(APPEND INCLUDES ${IMGUI_SRC_DIR})
list(APPEND LIBS imgui)

# Common library
add_library(common src/common/loadShader.cpp src/common/loadShader.hpp)
target_include_directories(common PUBLIC ${INCLUDES})
target_link_libraries(common ${LIBS})
list(APPEND INCLUDES src/common)
list(APPEND LIBS common)

# ImGui Example
add_executable(imgui-example src/imgui-example/main.cpp)
target_include_directories(imgui-example PUBLIC ${INCLUDES})
target_link_libraries(imgui-example ${LIBS})

# Tutorial 1
add_executable(tutorial-1 src/tutorial-1/main.cpp)
target_include_directories(tutorial-1 PUBLIC ${INCLUDES})
target_link_libraries(tutorial-1 ${LIBS})

# Tutorial 2
add_executable(tutorial-2 src/tutorial-2/main.cpp src/common/loadShader.cpp)
target_include_directories(tutorial-2 PUBLIC ${INCLUDES})
target_link_libraries(tutorial-2 ${LIBS})