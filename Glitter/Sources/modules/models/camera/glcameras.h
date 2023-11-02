//
// Created by fuwei on 2023/11/2.
//

#ifndef GLDEMOPLATFORM_GLCAMERAS_H
#define GLDEMOPLATFORM_GLCAMERAS_H

#include "Sources/modules/models/coordinate/glcoordinate.h"
#include <glm/glm.hpp>

class GlCameras : public GlCoordinate {
public:
  explicit GlCameras(GLFWwindow *window);
  ~GlCameras() = default;

protected:
  virtual void initVertexDatas() override;
  virtual void excuteTransforms() override;

  virtual void renderBeforeLoop() override;
  virtual void processInput() override;

private:
  float *m_vertices;
  glm::vec3 *m_cubePositions;
};

#endif // GLDEMOPLATFORM_GLCAMERAS_H
