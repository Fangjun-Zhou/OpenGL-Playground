#include <iostream>
#include <stdlib.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

int main(int argc, char const *argv[]) {
  std::cout << "GLFW OpenGL" << std::endl;

  // Init glfw.
  if (!glfwInit()) {
    std::cerr << "Failed to initialize GLFW" << std::endl;
    return EXIT_FAILURE;
  }

  // Create OpenGL window.
  glfwWindowHint(GLFW_SAMPLES, 4);
  // OpenGL 3.3
  glfwWindowHint(GLFW_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_VERSION_MINOR, 3);
  // Mac compatibility.
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  // Enable modern OpenGL.
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  // Open a window and create its OpenGL context.
  GLFWwindow *window;
  window = glfwCreateWindow(1024, 768, "Tutorial 01", NULL, NULL);
  if (window == NULL) {
    std::cerr << "Failed to open GLFW window. If you have an Intel GPU, they "
                 "are not 3.3 compatible. Try the 2.1 version of the tutorials."
              << std::endl;
    glfwTerminate();
    return EXIT_FAILURE;
  }
  glfwMakeContextCurrent(window);
  glewExperimental = true;
  if (glewInit() != GLEW_OK) {
    std::cerr << "Failed to initialize GLEW" << std::endl;
    return EXIT_FAILURE;
  }

  // Ensure we can capture the escape key being pressed below
  glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

  // Main loop.
  do {
    // Clear the screen.
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw nothing, see you in tutorial 2 !

    // Swap buffers.
    glfwSwapBuffers(window);
    glfwPollEvents();
  } while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
           glfwWindowShouldClose(window) == 0);

  return EXIT_SUCCESS;
}
