//
// Created by fuwei on 2023/10/30.
//

#include "gltrangleextent.h"
#include "Shaders/shaderutils.h"

GlTrangleExtent::GlTrangleExtent(GLFWwindow *window) : GLApplication(window) {}

void GlTrangleExtent::initShaders() {
  UNSIGNED_INT vertexShader = glCreateShader(GL_VERTEX_SHADER);
  GL_GET_SHADER_SOURCE(vertexShader, "vertextestshader");
  glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
  glCompileShader(vertexShader);
  checkShaderValid(vertexShader);

  UNSIGNED_INT fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  GL_GET_SHADER_SOURCE(fragmentShader, "fragmenttestshader");
  glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
  glCompileShader(fragmentShader);
  checkShaderValid(fragmentShader);

  m_shaderProgram = glCreateProgram();
  glAttachShader(m_shaderProgram, vertexShader);
  glAttachShader(m_shaderProgram, fragmentShader);
  glLinkProgram(m_shaderProgram);
  checkProgramValid(m_shaderProgram);

  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);
}

void GlTrangleExtent::initVertexDatas() {
  float vertices[] = {
      0.5f,  0.5f,  0.0f, // 右上角
      0.5f,  -0.5f, 0.0f, // 右下角
      -0.5f, -0.5f, 0.0f, // 左下角
      -0.5f, 0.5f,  0.0f  // 左上角
  };
  UNSIGNED_INT indices[] = {0, 1, 3, 1, 2, 3};

  glGenVertexArrays(1, &m_vaoArray);

  glGenBuffers(1, &m_vboArray);
  glGenBuffers(1, &m_eboArray);
  // bind the Vertex Array Object first, then bind and set vertex buffer(s), and
  // then configure vertex attributes(s).
  glBindVertexArray(m_vaoArray);

  glBindBuffer(GL_ARRAY_BUFFER, m_vboArray);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_eboArray);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices,
               GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
}

void GlTrangleExtent::executeRenders() {
  glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);

  glUseProgram(m_shaderProgram);
  glBindVertexArray(m_vaoArray);
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void GlTrangleExtent::clearDatas() {
  glDeleteVertexArrays(1, &m_vaoArray);
  glDeleteBuffers(1, &m_vboArray);
  glDeleteBuffers(1, &m_eboArray);
  glDeleteProgram(m_shaderProgram);
}