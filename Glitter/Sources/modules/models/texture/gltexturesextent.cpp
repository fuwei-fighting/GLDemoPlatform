//
// Created by fuwei on 2023/10/31.
//

#include "gltexturesextent.h"
#include "Shaders/shaderutils.h"

GlTexturesExtent::GlTexturesExtent(GLFWwindow *window) : GlTextures(window) {}

void GlTexturesExtent::initShaders() {
  UNSIGNED_INT vertexShader = glCreateShader(GL_VERTEX_SHADER);
  GL_GET_SHADER_SOURCE(vertexShader, "/texture/vertexshadertest");
  glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
  glCompileShader(vertexShader);
  checkShaderValid(vertexShader);

  UNSIGNED_INT fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  GL_GET_SHADER_SOURCE(fragmentShader, "/texture/fragmentshadertransform");
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

void GlTexturesExtent::processInput() {
  GLApplication::processInput();

  if (glfwGetKey(m_glWindow, GLFW_KEY_UP) == GLFW_PRESS) {
    m_mixValue += 0.01f;
    if (m_mixValue >= 1.0f) {
      m_mixValue = 1.0f;
    }
  }
  if (glfwGetKey(m_glWindow, GLFW_KEY_DOWN) == GLFW_PRESS) {
    m_mixValue -= 0.01f;
    if (m_mixValue <= 0.0f) {
      m_mixValue = 0.0f;
    }
  }
}

void GlTexturesExtent::loadTexture(const char *filePath, unsigned int &texture,
                                   unsigned int colorStyle) {
  GlTextures::loadTexture(filePath, texture, colorStyle);

  glUseProgram(m_shaderProgram);
  glUniform1i(glGetUniformLocation(m_shaderProgram, "inTexture"), 0);
  glUniform1i(glGetUniformLocation(m_shaderProgram, "outTexture"), 1);
}

void GlTexturesExtent::executeRenders() {
  GLApplication::executeRenders();

  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, m_textures[0]);
  glActiveTexture(GL_TEXTURE1);
  glBindTexture(GL_TEXTURE_2D, m_textures[1]);

  glUniform1f(glGetUniformLocation(m_shaderProgram, "mixValue"), m_mixValue);

  glUseProgram(m_shaderProgram);
  glBindVertexArray(m_vaoArray);
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
