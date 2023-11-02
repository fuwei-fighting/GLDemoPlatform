//
// Created by fuwei on 2023/10/31.
//

#ifndef GLDEMOPLATFORM_GLCOORDINATE_H
#define GLDEMOPLATFORM_GLCOORDINATE_H

#include "Sources/modules/models/texture/gltextures.h"

class GlCoordinate : public GlTextures {
public:
  explicit GlCoordinate(GLFWwindow *window);
  ~GlCoordinate() override = default;

protected:
  virtual void initShaders() override;
  virtual void initVertexDatas() override;
  virtual void loadTextures() override;
  virtual void executeRenders() override;

  //  virtual void renderBeforeLoop() override;

protected:
  virtual void excuteTransforms();

protected:
  // 将shaderPath作为类属性
  char *m_vertexPath;
  char *m_fragmentPath;
};

#endif // GLDEMOPLATFORM_GLCOORDINATE_H
