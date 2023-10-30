//
// Created by fuwei on 2023/10/30.
//

#include "glshaderinterpolation.h"
#include "Shaders/shaderutils.h"

GlShaderInterpolation::GlShaderInterpolation(GLFWwindow *window)
    : GLApplication(window) {}

void GlShaderInterpolation::initShaders() {
  // vertex shader
  UNSIGNED_INT vertexShader = glCreateShader(GL_VERTEX_SHADER);
  GL_GET_SHADER_SOURCE(vertexShader, "shaderinterpolation/vertexshader");
  glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
  glCompileShader(vertexShader);
  checkShaderValid(vertexShader);

  // fragment shader
  UNSIGNED_INT fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  GL_GET_SHADER_SOURCE(fragmentShader, "shaderinterpolation/fragmentshader");
  glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
  glCompileShader(fragmentShader);
  checkShaderValid(fragmentShader);

  // shader program
  m_shaderProgram = glCreateProgram();
  glAttachShader(m_shaderProgram, vertexShader);
  glAttachShader(m_shaderProgram, fragmentShader);
  glLinkProgram(m_shaderProgram);
  checkProgramValid(m_shaderProgram);

  // clear shaders
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);
}

void GlShaderInterpolation::initVertexDatas() {
  float vertices[] = {
      // 位置              // 颜色
      0.5f,  -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, // 右下
      -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, // 左下
      0.0f,  0.5f,  0.0f, 0.0f, 0.0f, 1.0f  // 顶部
  };
  glGenVertexArrays(1, &m_vaoArray);
  glGenBuffers(1, &m_vboArray);

  glBindVertexArray(m_vaoArray);

  glBindBuffer(GL_ARRAY_BUFFER, m_vboArray);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  // position attribute
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);
  // color attribute
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),
                        (void *)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);
}

void GlShaderInterpolation::executeRenders() {
  GLApplication::executeRenders();

  glUseProgram(m_shaderProgram);
  glBindVertexArray(m_vaoArray);

  glDrawArrays(GL_TRIANGLES, 0, 3);
}

void GlShaderInterpolation::clearDatas() {
  glDeleteVertexArrays(1, &m_vaoArray);
  glDeleteBuffers(1, &m_vboArray);
  glDeleteProgram(m_shaderProgram);
}
