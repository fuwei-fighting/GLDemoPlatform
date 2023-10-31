// Local Headers
#include "Shaders/shaderutils.h"
#include "glitter.hpp"
#include "modules/common/commondefine.h"
#include "modules/models/gllaunch.h"

#include "modules/models/modelhead.h"

// System Headers
#include <GLFW/glfw3.h>
#include <glad/glad.h>

// Standard Headers
#include <cstdio>
#include <cstdlib>

// glfw: whenever the window size changed (by OS or user resize) this callback
void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
  glViewport(0, 0, width, height);
}

int main(int argc, char *argv[]) {
  GLFW_INIT
#ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

  auto mWindow =
      glfwCreateWindow(kWindowWidth, kWindowHeight, "OpenGL", nullptr, nullptr);

  GLWINDOW_INIT(mWindow, framebuffer_size_callback)

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    fprintf(stderr, "Failed to initialize GLAD");
    return EXIT_FAILURE;
  }
  fprintf(stdout, "OpenGL %s, project path = %s.\n", glGetString(GL_VERSION),
          PROJECT_SOURCE_DIR);

  /*Application start*/
  GLApplication *app = new GlTexturesExtent(mWindow);
  app->launch();
  /*Application end*/

  return EXIT_SUCCESS;
}