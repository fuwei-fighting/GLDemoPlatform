//
// Created by fuwei on 2023/10/24.
//

#ifndef GLITTER_COMMONDEFINE_H
#define GLITTER_COMMONDEFINE_H

#define GLFW_INIT                                                              \
  glfwInit();                                                                  \
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);                               \
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);                               \
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#define GLWINDOW_INIT(window, callback)                                        \
  if (window == NULL) {                                                        \
    fprintf(stdout, "Failed to Create OpenGL Context");                        \
    return EXIT_FAILURE;                                                       \
  }                                                                            \
  glfwMakeContextCurrent(window);                                              \
  glfwSetFramebufferSizeCallback(window, callback);

#define UNSIGNED_INT unsigned int

/* GET SET */
#define DEFINE_PROPERTY_GET_SET(Class, property, Property)                     \
  Class get##Property() const;                                                 \
  void set##Property(const Class &property);

#define IMPLEMENT_PROPERTY_GET_SET(Class, property, Property)                  \
  Class get##Property() const { return m_##property; };                        \
  void set##Property(const Class &property) { m_##property = property; }

#endif // GLITTER_COMMONDEFINE_H
