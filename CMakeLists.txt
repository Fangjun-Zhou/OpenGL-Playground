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

# SPD Log
add_subdirectory(external/spdlog)
list(APPEND INCLUDES external/spdlog/include)
list(APPEND LIBS spdlog)

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

add_library(imgui ${IMGUI_SRC})
target_include_directories(
    imgui
    PUBLIC ${IMGUI_INCLUDES}
    PUBLIC external/glfw/include
)
target_link_libraries(imgui glfw)

list(APPEND INCLUDES ${IMGUI_SRC_DIR})
list(APPEND LIBS imgui)

# Common library
add_library(
    common
    src/common/loadShader.cpp
    src/common/loadShader.hpp
    src/common/pch.hpp
)
target_include_directories(common PUBLIC ${INCLUDES})
target_link_libraries(common ${LIBS})
target_precompile_headers(common PUBLIC src/common/pch.hpp)
list(APPEND INCLUDES src/common)
list(APPEND LIBS common)

# ImGui Example
add_executable(imgui_example src/imgui_example/main.cpp)
target_include_directories(imgui_example PUBLIC ${INCLUDES})
target_link_libraries(imgui_example ${LIBS})

# ImGui Example 2
add_executable(imgui_example_2 src/imgui_example_2/main.cpp)
target_include_directories(imgui_example_2 PUBLIC ${INCLUDES})
target_link_libraries(imgui_example_2 ${LIBS})

# Tutorial 1
add_executable(tutorial_1 src/tutorial_1/main.cpp)
target_include_directories(tutorial_1 PUBLIC ${INCLUDES})
target_link_libraries(tutorial_1 ${LIBS})

# Tutorial 2
add_executable(tutorial_2 src/tutorial_2/main.cpp src/common/loadShader.cpp)
target_include_directories(tutorial_2 PUBLIC ${INCLUDES})
target_link_libraries(tutorial_2 ${LIBS})

# Tutorial 3
add_executable(tutorial_3 src/tutorial_3/main.cpp src/common/loadShader.cpp)
target_include_directories(tutorial_3 PUBLIC ${INCLUDES})
target_link_libraries(tutorial_3 ${LIBS})