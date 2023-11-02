//
// Created by fuwei on 2023/10/30.
//
#include "stb_image.h"

#include "Shaders/shaderutils.h"
#include "Sources/modules/common/fileutil.h"
#include "gltextures.h"

constexpr char *kTextureContainerPath1 = "/resources/textures/container.jpg";
constexpr char *kTextureAwesomeFacePath1 =
    "/resources/textures/awesomeface.png";

GlTextures::GlTextures(GLFWwindow *window) : GLApplication(window) {}

void GlTextures::initShaders() {
  // vertex shader
  UNSIGNED_INT vertexShader = glCreateShader(GL_VERTEX_SHADER);
  GL_GET_SHADER_SOURCE(vertexShader, "texture/vertexshadertest");
  glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
  glCompileShader(vertexShader);
  checkShaderValid(vertexShader);

  // fragment shader
  UNSIGNED_INT fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  GL_GET_SHADER_SOURCE(fragmentShader, "texture/fragmentshadertest");
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

void GlTextures::initVertexDatas() {
  float vertices[] = {
      // positions          // colors           // texture coords
      0.5f,  0.5f,  0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // top right
      0.5f,  -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // bottom right
      -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom left
      -0.5f, 0.5f,  0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f  // top left
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
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);
  // color attribute
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
                        (void *)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);
  // texture coord attribute
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
                        (void *)(6 * sizeof(float)));
  glEnableVertexAttribArray(2);
}

void GlTextures::executeRenders() {
  GLApplication::executeRenders();

  // texture
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, m_textures[0]);
  glActiveTexture(GL_TEXTURE1);
  glBindTexture(GL_TEXTURE_2D, m_textures[1]);

  glUseProgram(m_shaderProgram);
  glBindVertexArray(m_vaoArray);
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void GlTextures::clearDatas() {
  glDeleteVertexArrays(1, &m_vaoArray);
  glDeleteBuffers(1, &m_vboArray);
  glDeleteBuffers(1, &m_eboArray);
}

void GlTextures::loadTexture(const char *filePath, UNSIGNED_INT &texture,
                             UNSIGNED_INT internalFormat, UNSIGNED_INT format) {
  std::string absPath = FileUtil::getModulesAbsNamePath(filePath);
  glGenTextures(1, &texture);
  glBindTexture(GL_TEXTURE_2D, texture);
  // 坐标轴纹理变化
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  // 放大缩小纹理变化
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  // load image, create texture and generate mipmaps
  int width, height, nrChannels;
  stbi_set_flip_vertically_on_load(true);
  unsigned char *data =
      stbi_load(absPath.c_str(), &width, &height, &nrChannels, 0);
  if (data) {
    glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format,
                 GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(
        GL_TEXTURE_2D); // 为当前绑定的纹理自动生成所有需要的多级渐远纹理
  } else {
    fprintf(stderr, "Failed to load texture, filePath = %s.", filePath);
  }
  stbi_image_free(data);
}

void GlTextures::loadTextures() {
  // 创建纹理
  m_textures.resize(2);
  loadTexture(kTextureContainerPath1, m_textures[0]);
  loadTexture(kTextureAwesomeFacePath1, m_textures[1], GL_RGBA);
  // 融合纹理
  glUseProgram(m_shaderProgram);
  glUniform1i(glGetUniformLocation(m_shaderProgram, "inTexture"), 0);
  glUniform1i(glGetUniformLocation(m_shaderProgram, "outTexture"), 1);
}
