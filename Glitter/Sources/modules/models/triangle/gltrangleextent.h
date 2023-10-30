//
// Created by fuwei on 2023/10/30.
//

#ifndef GLDEMOPLATFORM_GLTRANGLEEXTENT_H
#define GLDEMOPLATFORM_GLTRANGLEEXTENT_H

#include "Sources/modules/models/gllaunch.h"

class GlTrangleExtent : public GLApplication {
public:
  GlTrangleExtent(GLFWwindow *window);
  ~GlTrangleExtent() = default;

protected:
  void initShaders() override;

  void initVertexDatas() override;

  void executeRenders() override;

  void clearDatas() override;

private:
  UNSIGNED_INT m_shaderProgram;
  UNSIGNED_INT m_vaoArray;
  UNSIGNED_INT m_vboArray;
  UNSIGNED_INT m_eboArray;
};

#endif // GLDEMOPLATFORM_GLTRANGLEEXTENT_H
