//
// Created by fuwei on 2023/10/23.
//

#ifndef GLITTER_GLLAUNCH_H
#define GLITTER_GLLAUNCH_H

#include "../common/commondefine.h"
#include <GLFW/glfw3.h>
#include <glad/glad.h>

class GLApplication {
public:
  GLApplication(GLFWwindow *window);
  ~GLApplication() = default;

  GLFWwindow *glWindow() const { return m_glWindow; }
  void setGlWindow(GLFWwindow *window) { m_glWindow = window; }

private:
  GLFWwindow *m_glWindow = nullptr;
};

#endif // GLITTER_GLLAUNCH_H
