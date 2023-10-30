//
// Created by fuwei on 2023/10/23.
//

#include "gllaunch.h"
#include <cstdio>

GLApplication::GLApplication(GLFWwindow *window) : m_glWindow(window) {}

void GLApplication::launch() {
  /// make shaders and vertexs
  initShaders();
  initVertexDatas();

  // render loop
  while (!glfwWindowShouldClose(m_glWindow)) {
    processInput();
    // renders
    executeRenders();

    // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved
    glfwSwapBuffers(m_glWindow);
    glfwPollEvents();
  }
  clearDatas();
}

void GLApplication::executeRenders() {
  glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);
}

// process all input: query GLFW whether relevant keys are pressed/released this
void GLApplication::processInput() {
  if (glfwGetKey(m_glWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(m_glWindow, true);
}

void GLApplication::checkShaderValid(UNSIGNED_INT shader) {
  int success;
  char info[512];
  glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(shader, 512, NULL, info);
    fprintf(stderr, "ERROR::SHADER::COMPILATION_FAILED: %s. \n", info);
  }
}

void GLApplication::checkProgramValid(UNSIGNED_INT program) {
  int success;
  char info[512];
  glGetProgramiv(program, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(program, 512, NULL, info);
    fprintf(stderr, "ERROR::SHADER::PROGRAM::COMPILATION_FAILED: %s. \n", info);
  }
}