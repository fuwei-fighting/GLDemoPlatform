//
// Created by fuwei on 2023/10/31.
//
#include "stb_image.h"

#include "Shaders/shaderutils.h"
#include "Sources/modules/common/fileutil.h"
#include "gltransforms.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

constexpr char *kTextureContainerPath = "/resources/textures/container.jpg";
constexpr char *kTextureAwesomeFacePath = "/resources/textures/awesomeface.png";

GlTransforms::GlTransforms(GLFWwindow *window) : GLApplication(window) {}

void GlTransforms::initShaders() {
  // vertex shader
  UNSIGNED_INT vertexShader = glCreateShader(GL_VERTEX_SHADER);
  GL_GET_SHADER_SOURCE(vertexShader, "transforms/vertexshadertest");
  glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
  glCompileShader(vertexShader);
  checkShaderValid(vertexShader);

  // fragment shader
  UNSIGNED_INT fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  GL_GET_SHADER_SOURCE(fragmentShader, "transforms/fragmentshadertest");
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

void GlTransforms::initVertexDatas() {
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

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);

  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float),
                        (void *)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);
}

void GlTransforms::executeRenders() {
  GLApplication::executeRenders();

  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, m_textures[0]);
  glActiveTexture(GL_TEXTURE1);
  glBindTexture(GL_TEXTURE_2D, m_textures[1]);

  loadTransforms();
}

void GlTransforms::clearDatas() {
  glDeleteVertexArrays(1, &m_vaoArray);
  glDeleteBuffers(1, &m_vboArray);
  glDeleteBuffers(1, &m_eboArray);
}

void GlTransforms::loadTextures() {
  m_textures.resize(2);
  loadTexture(m_textures[0], kTextureContainerPath);
  loadTexture(m_textures[1], kTextureAwesomeFacePath, GL_REPEAT, GL_LINEAR,
              GL_RGBA);

  glUseProgram(m_shaderProgram);
  glUniform1i(glGetUniformLocation(m_shaderProgram, "texture1"), 0);
  glUniform1i(glGetUniformLocation(m_shaderProgram, "texture2"), 1);
}

void GlTransforms::loadTexture(UNSIGNED_INT &texture, const char *filePath,
                               UNSIGNED_INT wrapping, UNSIGNED_INT filter,
                               UNSIGNED_INT colorStyle) {
  std::string absPath = FileUtil::getModulesAbsNamePath(filePath);
  glGenTextures(1, &texture);
  glBindTexture(GL_TEXTURE_2D, texture);

  // set the texture wrapping parameters
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapping);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapping);
  // set texture filtering parameters
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter);
  // load image, create texture and generate mipmaps
  int width, height, nrChannels;
  UNSIGNED_CHAR *data =
      stbi_load(absPath.c_str(), &width, &height, &nrChannels, 0);
  if (data) {
    glTexImage2D(GL_TEXTURE_2D, 0, colorStyle, width, height, 0, colorStyle,
                 GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
  } else {
    fprintf(stderr, "Failed to load texture, filePath = %s.", filePath);
  }
  stbi_image_free(data);
}

void GlTransforms::loadTransforms() {
  // transforms
  glm::mat4 transform = glm::mat4(1.0f);
  transform = glm::translate(transform, glm::vec3(0.5f, -0.5f, 0.0f));
  transform =
      glm::rotate(transform, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));

  glUseProgram(m_shaderProgram);
  UNSIGNED_INT transformLoc =
      glGetUniformLocation(m_shaderProgram, "transform");
  glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));

  glBindVertexArray(m_vaoArray);
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

  // second
  transform = glm::mat4(1.0f);
  transform = glm::translate(transform, glm::vec3(-0.5f, 0.5f, 0.0f));
  float scaleAmount = static_cast<float>(sin(glfwGetTime()));
  transform =
      glm::scale(transform, glm::vec3(scaleAmount, scaleAmount, scaleAmount));
  glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

  // third
  transform = glm::mat4(1.0f);
  transform = glm::translate(transform, glm::vec3(0.5f, 0.5f, 0.0f));
  transform =
      glm::scale(transform, glm::vec3(scaleAmount, scaleAmount, scaleAmount));
  glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));

  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
  // 调用glDrawElements几次就会画几个，如果画的图像发生变化，需要重新bindVertex
  // 或 bindTexture
}