#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

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

  // Init ImGui context.
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO &io = ImGui::GetIO();
  // Enable keyboard.
  io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
  // Enable docking.
  io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
  // Enable multi viewport.
  io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

  // Set ImGui style.
  ImGui::StyleColorsDark();

  // Setup render backend.
  ImGui_ImplGlfw_InitForOpenGL(window, true);
  ImGui_ImplOpenGL3_Init("#version 150");

  // Load fonts.
  ImFont *font = io.Fonts->AddFontFromFileTTF(
      "resources/Roboto/Roboto-Regular.ttf", 16.0f);
  // Check if the font is loaded correctly.
  if (!font) {
    consoleLogger->error("Font not loaded.");
  }

  if (glewInit() != GLEW_OK) {
    consoleLogger->error("GLEW initialization failed.");
    glfwTerminate();
    return EXIT_FAILURE;
  }

  while (!glfwWindowShouldClose(window)) {
    // Poll events.
    glfwPollEvents();
    // Clear screen.
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // ImGui frame.
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    {
      static float f = 0.0f;
      static int counter = 0;

      ImGui::Begin("Hello, world!");

      ImGui::Text("This is some useful text.");

      ImGui::SliderFloat("float", &f, 0.0f, 1.0f);

      if (ImGui::Button("Button")) counter++;
      ImGui::SameLine();
      ImGui::Text("counter = %d", counter);

      ImGui::Text("Application average %.3f ms/frame (%.1f FPS)",
                  1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
      ImGui::End();
    }

    // Rendering.
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
      GLFWwindow *backup_current_context = glfwGetCurrentContext();
      ImGui::UpdatePlatformWindows();
      ImGui::RenderPlatformWindowsDefault();
      glfwMakeContextCurrent(backup_current_context);
    }

    // Swap buffers.
    glfwSwapBuffers(window);
  }

  // Cleanup
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();

  glfwDestroyWindow(window);
  glfwTerminate();

  return EXIT_SUCCESS;
}
