//
// Created by fuwei on 2023/10/29.
//

#include "gltriangle.h"
#include "Shaders/shaderutils.h"

GlTriangle::GlTriangle(GLFWwindow *window) : GLApplication(window) {}

void GlTriangle::initShaders() {
  UNSIGNED_INT vertexShader = glCreateShader(GL_VERTEX_SHADER);
  std::string vertexShaderStr = ShaderUtils::readShaderSource(
      ShaderUtils::getShaderAbsPath("vertextestshader"));
  const char *vertexShaderSource = vertexShaderStr.c_str();
  glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
  glCompileShader(vertexShader);

  int success;
  char info[512];
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(vertexShader, 512, NULL, info);
    fprintf(stderr, "ERROR::SHADER::VERTEX::COMPILATION_FAILED %s \n", info);
  }

  unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  std::string fragmentShaderStr = ShaderUtils::readShaderSource(
      ShaderUtils::getShaderAbsPath("fragmenttestshader"));
  const char *fragmentShaderSource = fragmentShaderStr.c_str();
  glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
  glCompileShader(fragmentShader);
  // check for shader compile errors
  glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(fragmentShader, 512, NULL, info);
    fprintf(stderr, "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED %s \n", info);
  }

  // fragment shader
  //    UNSIGNED_INT shaderProgram = glCreateProgram();
  m_shaderProgram = glCreateProgram();
  glAttachShader(m_shaderProgram, vertexShader);
  glAttachShader(m_shaderProgram, fragmentShader);

  glLinkProgram(m_shaderProgram);
  glGetProgramiv(m_shaderProgram, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(m_shaderProgram, 512, NULL, info);
    fprintf(stderr, "ERROR::SHADER::PROGRAM::LINKING_FAILED %s \n", info);
  }
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);
}

void GlTriangle::initVertexDatas() {
  float vertices[] = {
      -0.5f, -0.5f, 0.0f, // left
      0.5f,  -0.5f, 0.0f, // right
      0.0f,  0.5f,  0.0f  // top
  };
  UNSIGNED_INT VBO, VAO;
  glGenVertexArrays(1, &m_vaoArray);
  glGenBuffers(1, &VBO);

  glBindVertexArray(m_vaoArray);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);

  glBindBuffer(GL_ARRAY_BUFFER, 0);

  glBindVertexArray(0);
}

void GlTriangle::executeRenders() {
  glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);

  glUseProgram(m_shaderProgram);
  glBindVertexArray(m_vaoArray);
  glDrawArrays(GL_TRIANGLES, 0, 3);
}
