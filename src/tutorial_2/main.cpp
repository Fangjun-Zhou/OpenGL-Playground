#include "pch.hpp"

#include "loadShader.hpp"

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
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  // Mac compatibility.
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  // Enable modern OpenGL.
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  // Open a window and create its OpenGL context.
  GLFWwindow *window;
  window = glfwCreateWindow(1024, 768, "Tutorial 02", NULL, NULL);
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

  // Create VAO
  GLuint VertexArrayID;
  glGenVertexArrays(1, &VertexArrayID);
  glBindVertexArray(VertexArrayID);

  // GL vertex data.
  static const GLfloat vertexBufferData[] = {
      -1.0f, -1.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
  };

  // Generate vertex buffer.
  GLuint vertexBuffer;
  glGenBuffers(1, &vertexBuffer);
  glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertexBufferData), vertexBufferData,
               GL_STATIC_DRAW);

  // Ensure we can capture the escape key being pressed below
  glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

  GLuint programID = LoadShaders("simple-vert.vert", "simple-frag.frag");

  // Main loop.
  do {
    // Clear the screen.
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Use shader.
    glUseProgram(programID);

    // Draw triangle.
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glDisableVertexAttribArray(0);

    // Swap buffers.
    glfwSwapBuffers(window);
    glfwPollEvents();
  } while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
           glfwWindowShouldClose(window) == 0);

  return EXIT_SUCCESS;
}
