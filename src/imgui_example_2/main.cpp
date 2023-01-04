#include <imgui.h>

#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

auto consoleLogger = spdlog::stdout_color_mt("console");

int main(int argc, char const *argv[]) {
  consoleLogger->info("ImGui App Example.");

  // Init glfw.
  if (!glfwInit()) {
    consoleLogger->error("GLFW initialization failed.");

    return EXIT_FAILURE;
  }

  // Enable 4xMSAA anti-aliasing.
  glfwWindowHint(GLFW_SAMPLES, 4);
  // OpenGL 3.3.
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  // MacOS compatability.
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
  // Enable modern OpenGL.
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  // Create GLFW window.
  GLFWwindow *window = glfwCreateWindow(960, 540, "ImGui Demo", NULL, NULL);

  if (!window) {
    consoleLogger->error("GLFW window creation failed.");
    glfwTerminate();
    return EXIT_FAILURE;
  }

  // Make glfw context current.
  glfwMakeContextCurrent(window);
  glewExperimental = true;

  if (glewInit() != GLEW_OK) {
    consoleLogger->error("GLEW initialization failed.");
    glfwTerminate();
    return EXIT_FAILURE;
  }

  while (!glfwWindowShouldClose(window)) {
    // Clear screen.
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Swap buffers.
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  return EXIT_SUCCESS;
}
