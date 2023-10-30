//
// Created by fuwei on 2023/10/30.
//

#include "glshaderuniform.h"
#include "Shaders/shaderutils.h"

#include "glitter.hpp"

#include <iostream>

GlShaderUniform::GlShaderUniform(GLFWwindow *window) : GLApplication(window) {}

void GlShaderUniform::initShaders() {
  // vertex shader
  UNSIGNED_INT vertexShader = glCreateShader(GL_VERTEX_SHADER);
  GL_GET_SHADER_SOURCE(vertexShader, "shaderuniform/vertexshader");
  glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
  glCompileShader(vertexShader);
  checkShaderValid(vertexShader);

  // fragment shader
  UNSIGNED_INT fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  GL_GET_SHADER_SOURCE(fragmentShader, "shaderuniform/fragmentshader");
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

void GlShaderUniform::initVertexDatas() {
  float vertices[] = {
      0.5f,  -0.5f, 0.0f, // bottom right
      -0.5f, -0.5f, 0.0f, // bottom left
      0.0f,  0.5f,  0.0f  // top
  };
  glGenVertexArrays(1, &m_vaoArray);
  glGenBuffers(1, &m_vboArray);
  // bind the Vertex Array Object first, then bind and set vertex buffer(s), and
  // then configure vertex attributes(s).
  glBindVertexArray(m_vaoArray);

  glBindBuffer(GL_ARRAY_BUFFER, m_vboArray);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);
  glBindVertexArray(m_vaoArray);
}

void GlShaderUniform::executeRenders() {
  GLApplication::executeRenders();

  glUseProgram(m_shaderProgram); // activate shader program
  double timeValue = glfwGetTime();
  float greenValue = static_cast<float>(sin(timeValue) / 2.0 + 0.5);

  // uniform
  int vertexColorLocation = glGetUniformLocation(m_shaderProgram, "outColor");
  glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);

  // exercise 2
  // 这是一个移动动画
  double moveStep = glfwGetTime() * 100;
  float xDist = fmod(moveStep, kWindowWidth) / kWindowWidth;
  glUniform1f(glGetUniformLocation(m_shaderProgram, "xDist"), xDist);

  glDrawArrays(GL_TRIANGLES, 0, 3);
}

void GlShaderUniform::clearDatas() {
  glDeleteVertexArrays(1, &m_vaoArray);
  glDeleteBuffers(1, &m_vboArray);
  glDeleteProgram(m_shaderProgram);
}
