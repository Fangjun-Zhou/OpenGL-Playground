#include <pch.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "loadShader.hpp"
#include "vertex.h"

// The width and height of current glfw window.
int windowWidth, windowHeight;

void windowResizeCallback(GLFWwindow *window, int width, int height) {
  windowWidth = width;
  windowHeight = height;
}

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

  // Set GLFW window resize callback and get current window size.
  glfwSetWindowSizeCallback(window, windowResizeCallback);
  glfwGetWindowSize(window, &windowWidth, &windowHeight);

  glfwMakeContextCurrent(window);
  glewExperimental = true;
  if (glewInit() != GLEW_OK) {
    std::cerr << "Failed to initialize GLEW" << std::endl;
    return EXIT_FAILURE;
  }

  // Create VAO.
  GLuint vertexArray;
  glGenVertexArrays(1, &vertexArray);
  glBindVertexArray(vertexArray);

  // GL vertex data.
  static const Vertex vertexBufferData[] = {
      {{-1.0f, -1.0f, 0.0f}, {1.0f, 0.0f, 0.0f, 1.0f}},
      {{1.0f, -1.0f, 0.0f}, {0.0f, 1.0f, 0.0f, 1.0f}},
      {{0.0f, 1.0f, 0.0f}, {0.0f, 0.0f, 1.0f, 1.0f}},
  };

  // Generate vertex buffer.
  GLuint vertexBuffer;
  glGenBuffers(1, &vertexBuffer);
  glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertexBufferData), vertexBufferData,
               GL_STATIC_DRAW);

  // Ensure we can capture the escape key being pressed below
  glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

  GLuint programId = LoadShaders("src/tutorial_3/simple-vert.vert",
                                 "src/tutorial_3/simple-frag.frag");

  // Main loop.
  do {
    // Generate the projection matrix.
    glm::mat4 matProjection = glm::perspective(
        glm::radians(45.0f), (float)windowWidth / (float)windowHeight, 0.1f,
        100.0f);

    // Generate the view matrix.
    // Camera at (4, 3, 3), look at (0, 0, 0), up is (0, 1, 0).
    glm::mat4 matView =
        glm::lookAt(glm::vec3(4, 3, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));

    // Generate the model matrix.
    glm::mat4 matModel = glm::mat4(1.0f);

    // Generate the mvp matrix.
    glm::mat4 matMVP = matProjection * matView * matModel;

    // Clear the screen.
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Use shader.
    glUseProgram(programId);

    // Draw triangle.
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    // Vertex position attribute.
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)0);
    // Vertex color attribute.
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                          (const void *)offsetof(Vertex, color));

    // Get the uniform mvp matrix.
    GLuint matMVPId = glGetUniformLocation(programId, "u_mvp");
    glUniformMatrix4fv(matMVPId, 1, GL_FALSE, &matMVP[0][0]);

    glDrawArrays(GL_TRIANGLES, 0, 3);

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);

    // Swap buffers.
    glfwSwapBuffers(window);
    glfwPollEvents();
  } while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
           glfwWindowShouldClose(window) == 0);

  return EXIT_SUCCESS;
}
