//
// Created by fuwei on 2023/10/29.
//

#ifndef GLDEMOPLATFORM_GLTRIANGLE_H
#define GLDEMOPLATFORM_GLTRIANGLE_H

#include "Sources/modules/models/gllaunch.h"

class GlTriangle : public GLApplication {
public:
  GlTriangle(GLFWwindow *window);

private:
  void initShaders() override;
  void initVertexDatas() override;
  void executeRenders() override;

  void clearDatas() override;

private:
  UNSIGNED_INT m_shaderProgram;
  UNSIGNED_INT m_vaoArray;
  UNSIGNED_INT m_vboArray;
};

#endif // GLDEMOPLATFORM_GLTRIANGLE_H
