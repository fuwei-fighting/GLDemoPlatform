//
// Created by fuwei on 2023/10/31.
//

#include "glcoordinate.h"
#include "Shaders/shaderutils.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

constexpr char *kTextureContainerPath2 = "/resources/textures/container.jpg";
constexpr char *kTextureAwesomeFacePath2 =
    "/resources/textures/awesomeface.png";

GlCoordinate::GlCoordinate(GLFWwindow *window) : GlTextures(window) {
  m_vertexPath = "coordinate/vertexshadertest";
  m_fragmentPath = "coordinate/fragmentshadertest";
}

void GlCoordinate::initShaders() {
  // vertex shader
  UNSIGNED_INT vertexShader = glCreateShader(GL_VERTEX_SHADER);
  GL_GET_SHADER_SOURCE(vertexShader, m_vertexPath);
  glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
  glCompileShader(vertexShader);
  checkShaderValid(vertexShader);

  // fragment shader
  UNSIGNED_INT fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  GL_GET_SHADER_SOURCE(fragmentShader, m_fragmentPath);
  glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
  glCompileShader(fragmentShader);
  checkShaderValid(fragmentShader);

  // shader program
  m_shaderProgram = glCreateProgram();
  glAttachShader(m_shaderProgram, vertexShader);
  glAttachShader(m_shaderProgram, fragmentShader);
  glLinkProgram(m_shaderProgram);
  checkProgramValid(m_shaderProgram);

  // clear shader
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);
}

void GlCoordinate::initVertexDatas() {
  float vertices[] = {
      // positions          // texture coords
      0.5f,  0.5f,  0.0f, 1.0f, 1.0f, // top right
      0.5f,  -0.5f, 0.0f, 1.0f, 0.0f, // bottom right
      -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, // bottom left
      -0.5f, 0.5f,  0.0f, 0.0f, 1.0f  // top left
  };
  unsigned int indices[] = {
      0, 1, 3, // first triangle
      1, 2, 3  // second triangle
  };
  glGenVertexArrays(1, &m_vaoArray);
  glGenBuffers(1, &m_vboArray);
  glGenBuffers(1, &m_eboArray);

  glBindVertexArray(m_vaoArray);

  glBindBuffer(GL_ARRAY_BUFFER, m_vboArray);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_eboArray);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices,
               GL_STATIC_DRAW);

  // position attribute
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);
  // texture coord attribute
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float),
                        (void *)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);
}

void GlCoordinate::loadTextures() {
  m_textures.resize(2);
  loadTexture(kTextureContainerPath2, m_textures[0]);
  loadTexture(kTextureAwesomeFacePath2, m_textures[1], GL_RGB, GL_RGBA);
  // 融合纹理
  glUseProgram(m_shaderProgram);
  glUniform1i(glGetUniformLocation(m_shaderProgram, "texture1"), 0);
  glUniform1i(glGetUniformLocation(m_shaderProgram, "texture2"), 1);
}

void GlCoordinate::executeRenders() {
  glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, m_textures[0]);
  glActiveTexture(GL_TEXTURE1);
  glBindTexture(GL_TEXTURE_2D, m_textures[1]);

  excuteTransforms();
}

void GlCoordinate::excuteTransforms() {
  glUseProgram(m_shaderProgram);
  // create transformations
  glm::mat4 model = glm::mat4(1.0f);
  glm::mat4 view = glm::mat4(1.0f);
  glm::mat4 projection = glm::mat4(1.0f);

  model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
  view = glm::translate(view, glm::vec3(0.0f, 0.0f, -5.0f));
  projection = glm::perspective(glm::radians(45.0f), (float)800 / (float)600,
                                0.1f, 100.0f);
  UNSIGNED_INT modelLoc = glGetUniformLocation(m_shaderProgram, "model");
  UNSIGNED_INT viewLoc = glGetUniformLocation(m_shaderProgram, "view");
  UNSIGNED_INT projectLoc = glGetUniformLocation(m_shaderProgram, "projection");

  glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
  glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
  glUniformMatrix4fv(projectLoc, 1, GL_FALSE, glm::value_ptr(projection));

  glBindVertexArray(m_vaoArray);
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}