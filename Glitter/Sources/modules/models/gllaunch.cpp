//
// Created by fuwei on 2023/10/23.
//

#include "gllaunch.h"

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