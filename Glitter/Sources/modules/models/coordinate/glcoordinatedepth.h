//
// Created by fuwei on 2023/11/1.
//

#ifndef GLDEMOPLATFORM_GLCOORDINATEDEPTH_H
#define GLDEMOPLATFORM_GLCOORDINATEDEPTH_H

#include "glcoordinate.h"

class GlCoordinateDepth : public GlCoordinate {
public:
  explicit GlCoordinateDepth(GLFWwindow *window);
  ~GlCoordinateDepth() = default;

private:
  void initVertexDatas() override;
  void excuteTransforms() override;
};

#endif // GLDEMOPLATFORM_GLCOORDINATEDEPTH_H
