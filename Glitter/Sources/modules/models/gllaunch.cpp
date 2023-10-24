//
// Created by fuwei on 2023/10/23.
//

#include "gllaunch.h"

#include <cstdio>
#include <cstdlib>

static constexpr int kWindowWidth = 800;
static constexpr int kWindowHeight = 600;

GLApplication::GLApplication(GLFWwindow *window) : m_glWindow(window) {}
