//
// Created by fuwei on 2023/10/30.
//

#ifndef GLDEMOPLATFORM_GLSHADERINTERPOLATION_H
#define GLDEMOPLATFORM_GLSHADERINTERPOLATION_H

#include "Sources/modules/models/gllaunch.h"

class GlShaderInterpolation : public GLApplication {
public:
  explicit GlShaderInterpolation(GLFWwindow *window);
  ~GlShaderInterpolation() override = default;

private:
  void initShaders() override;
  void initVertexDatas() override;
  void executeRenders() override;
  void clearDatas() override;

private:
  UNSIGNED_INT m_shaderProgram;
  // vertexs
  UNSIGNED_INT m_vaoArray;
  UNSIGNED_INT m_vboArray;
};

#endif // GLDEMOPLATFORM_GLSHADERINTERPOLATION_H
