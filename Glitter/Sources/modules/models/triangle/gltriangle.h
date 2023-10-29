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
};

#endif // GLDEMOPLATFORM_GLTRIANGLE_H
