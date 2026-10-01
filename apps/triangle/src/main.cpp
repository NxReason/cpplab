#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

const int SIDEBAR_WIDTH = 300;

void framebuffer_size_callback(GLFWwindow*, int width, int height) {
  glViewport(SIDEBAR_WIDTH, 0, width - SIDEBAR_WIDTH, height);
}

GLFWwindow* createWindow(int width, int height, const char* title) {
  if (!glfwInit()) {
    std::cerr << "Failed to initialize GLFW\n";
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLFWwindow* window = glfwCreateWindow(
    width,
    height,
    title,
    nullptr,
    nullptr
  );

  if (!window) {
    std::cerr << "Failed to create window\n";
    glfwTerminate();
    return nullptr;
  }

  glfwMakeContextCurrent(window);

  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cerr << "Failed to initialize GLAD\n";
    glfwDestroyWindow(window);
    glfwTerminate();
    return nullptr;
  }

  return window;
}

GLuint createShader(GLenum type, const char* source) {
  GLuint shader = glCreateShader(type);

  glShaderSource(shader, 1, &source, nullptr);
  glCompileShader(shader);

  int success;
  glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
  if (!success) {
    char info[512];
    glGetShaderInfoLog(shader, 512, nullptr, info);
    std::cerr << info << '\n';
  }
  return shader;
}

GLuint createShaderProgram() {
  const char* fragmentShader =
    R"(
    #version 330 core

    out vec4 FragColor;

    void main() {
      FragColor = vec4(0.2, 0.7, 1.0, 1.0);
    }
    )";
  const char* vertexShader =
    R"(
    #version 330 core

    layout(location = 0) in vec3 aPos;

    void main() {
      gl_Position = vec4(aPos, 1.0);
    }
    )";

  GLuint vertex = createShader(GL_VERTEX_SHADER, vertexShader);
  GLuint fragment = createShader(GL_FRAGMENT_SHADER, fragmentShader);

  GLuint program = glCreateProgram();

  glAttachShader(program, vertex);
  glAttachShader(program, fragment);

  glLinkProgram(program);

  glDeleteShader(vertex);
  glDeleteShader(fragment);

  return program;
}

int main() {
  GLFWwindow* window = createWindow(800 + SIDEBAR_WIDTH, 600, "Triangle");
  if (!window) return -1;
  glViewport(SIDEBAR_WIDTH, 0, 800, 600);

  // UI
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();

  ImGuiIO& io = ImGui::GetIO();
  io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
  // io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
  ImGui::StyleColorsDark();

  ImGui_ImplGlfw_InitForOpenGL(window, true);
  ImGui_ImplOpenGL3_Init("#version 330");

  // app data
  float vertices[] = {
     0.0f,  0.5f, 0.0f,
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f
  };

  GLuint VAO;
  GLuint VBO;

  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);

  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
  glEnableVertexAttribArray(0);

  GLuint shader = createShaderProgram();

  auto saveFunc = []() {
    std::cout << "saving" << std::endl;
  };
  char buf[32];
  float f = 0.0f;

  glClearColor(0.1f, 0.1f, 0.15f, 1.0f);
  auto imGuiWindowFlags = 
    ImGuiWindowFlags_NoMove | 
    ImGuiWindowFlags_NoResize |
    ImGuiWindowFlags_NoCollapse;
  while (!glfwWindowShouldClose(window)) {
    glfwPollEvents();

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();

    ImGui::NewFrame();
    // ImGui::DockSpaceOverViewport(
    //   0,
    //   ImGui::GetMainViewport(),
    //   ImGuiDockNodeFlags_PassthruCentralNode
    // );
    ImGui::SetNextWindowPos(ImVec2(0, 0));
    ImGui::SetNextWindowSize(ImVec2(300, ImGui::GetIO().DisplaySize.y));

    ImGui::Begin("Scene", nullptr, imGuiWindowFlags);
    if (ImGui::Button("Save")) {
      saveFunc();
    }
    ImGui::SliderFloat("float", &f, 0.0f, 1.0f);
    ImGui::InputText("string", buf, IM_COUNTOF(buf));
    ImGui::End();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(shader);
    glad_glBindVertexArray(VAO);

    glDrawArrays(GL_TRIANGLES, 0, 3);

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    // if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
    //   ImGui::UpdatePlatformWindows();
    //   ImGui::RenderPlatformWindowsDefault();
    // }

    glfwSwapBuffers(window);
  }

  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);

  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();

  glfwDestroyWindow(window);
  glfwTerminate();

  return 0;
}