//
// Created by fuwei on 2023/10/30.
//

#ifndef GLDEMOPLATFORM_GLTEXTURES_H
#define GLDEMOPLATFORM_GLTEXTURES_H

#include "Sources/modules/models/gllaunch.h"

#include <string>

class GlTextures : public GLApplication {
public:
  explicit GlTextures(GLFWwindow *window);
  ~GlTextures() = default;

protected:
  virtual void initShaders() override;
  virtual void initVertexDatas() override;
  virtual void executeRenders() override;
  void clearDatas() override;

protected:
  virtual void loadTexture(const char *filePath, UNSIGNED_INT &texture,
                           UNSIGNED_INT colorStyle = GL_RGB);

protected:
  // shader
  UNSIGNED_INT m_shaderProgram;
  // vertex
  UNSIGNED_INT m_vaoArray;
  UNSIGNED_INT m_vboArray;
  UNSIGNED_INT m_eboArray;
  // textures
  std::vector<UNSIGNED_INT> m_textures;
};

#endif // GLDEMOPLATFORM_GLTEXTURES_H
