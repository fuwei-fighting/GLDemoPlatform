//
// Created by fuwei on 2023/10/31.
//

#ifndef GLDEMOPLATFORM_GLTEXTURESEXTENT_H
#define GLDEMOPLATFORM_GLTEXTURESEXTENT_H

#include "gltextures.h"

class GlTexturesExtent : public GlTextures {
public:
  explicit GlTexturesExtent(GLFWwindow *window);
  ~GlTexturesExtent() = default;

private:
  void processInput() override;
  void loadTexture(const char *filePath, unsigned int &texture,
                   unsigned int colorStyle) override;
  void executeRenders() override;

protected:
  void initShaders() override;

private:
  float m_mixValue = 0.2f;
};

#endif // GLDEMOPLATFORM_GLTEXTURESEXTENT_H
