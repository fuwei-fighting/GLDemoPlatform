//
// Created by fuwei on 2023/10/31.
//

#ifndef GLDEMOPLATFORM_GLTRANSFORMS_H
#define GLDEMOPLATFORM_GLTRANSFORMS_H

#include "Sources/modules/models/gllaunch.h"

#include <vector>

class GlTransforms : public GLApplication {
public:
  explicit GlTransforms(GLFWwindow *window);
  ~GlTransforms() override = default;

protected:
  virtual void loadTransforms();

private:
  void initShaders() override;
  void initVertexDatas() override;
  void executeRenders() override;
  void clearDatas() override;

  void loadTextures() override;

  void loadTexture(UNSIGNED_INT &texture, const char *filePath,
                   UNSIGNED_INT wrapping = GL_REPEAT,
                   UNSIGNED_INT filter = GL_LINEAR,
                   UNSIGNED_INT colorStyle = GL_RGB);

private:
  // shader
  UNSIGNED_INT m_shaderProgram;
  // vertex
  UNSIGNED_INT m_vaoArray;
  UNSIGNED_INT m_vboArray;
  UNSIGNED_INT m_eboArray;
  // textures
  std::vector<UNSIGNED_INT> m_textures;
};

#endif // GLDEMOPLATFORM_GLTRANSFORMS_H
