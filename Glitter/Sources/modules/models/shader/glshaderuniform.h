//
// Created by fuwei on 2023/10/30.
//

#ifndef GLDEMOPLATFORM_GLSHADERUNIFORM_H
#define GLDEMOPLATFORM_GLSHADERUNIFORM_H

#include "Sources/modules/models/gllaunch.h"

class GlShaderUniform : public GLApplication {
public:
  GlShaderUniform(GLFWwindow *window);
  ~GlShaderUniform() = default;

private:
  void initShaders() override;
  void initVertexDatas() override;
  void executeRenders() override;
  void clearDatas() override;

private:
  // shaders
  UNSIGNED_INT m_shaderProgram;
  // vertexs
  UNSIGNED_INT m_vaoArray;
  UNSIGNED_INT m_vboArray;
};

#endif // GLDEMOPLATFORM_GLSHADERUNIFORM_H
