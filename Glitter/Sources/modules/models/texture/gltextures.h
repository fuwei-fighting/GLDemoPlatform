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

private:
  void initShaders() override;
  void initVertexDatas() override;
  void executeRenders() override;
  void clearDatas() override;

protected:
  void loadTexture(const char *filePath);

private:
  // shader
  UNSIGNED_INT m_shaderProgram;
  // vertex
  UNSIGNED_INT m_vaoArray;
  UNSIGNED_INT m_vboArray;
  UNSIGNED_INT m_eboArray;
  // texture
  UNSIGNED_INT m_texture;
};

#endif // GLDEMOPLATFORM_GLTEXTURES_H
