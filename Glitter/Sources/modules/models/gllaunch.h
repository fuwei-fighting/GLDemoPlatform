//
// Created by fuwei on 2023/10/23.
//

#ifndef GLITTER_GLLAUNCH_H
#define GLITTER_GLLAUNCH_H

#include "../common/commondefine.h"
#include <GLFW/glfw3.h>
#include <glad/glad.h>

class GLApplication {
public:
  GLApplication(GLFWwindow *window);
  virtual ~GLApplication() = default;

  /// 模板方法：这个方法如果不需要重写，那就可以是个non-virtual function
  void launch();

protected:
  virtual void processInput();

  virtual void initShaders() = 0;
  virtual void initVertexDatas() = 0;
  virtual void executeRenders();

protected:
  GLFWwindow *m_glWindow = nullptr;
  UNSIGNED_INT m_shaderProgram;
  UNSIGNED_INT m_vaoArray;
};

#endif // GLITTER_GLLAUNCH_H
