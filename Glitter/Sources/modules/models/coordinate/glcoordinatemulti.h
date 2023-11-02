//
// Created by fuwei on 2023/11/1.
//

#ifndef GLDEMOPLATFORM_GLCOORDINATEMULTI_H
#define GLDEMOPLATFORM_GLCOORDINATEMULTI_H

#include "glcoordinate.h"
#include <glm/glm.hpp>

class GlCoordinateMulti : public GlCoordinate {
public:
  explicit GlCoordinateMulti(GLFWwindow *window);
  ~GlCoordinateMulti() = default;

private:
  void initVertexDatas() override;
  void excuteTransforms() override;

private:
  float *m_vertices;
  glm::vec3 *m_cubePositions;
};

#endif // GLDEMOPLATFORM_GLCOORDINATEMULTI_H
