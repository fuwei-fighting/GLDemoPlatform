//
// Created by fuwei on 2023/10/28.
//

#ifndef GLDEMOPLATFORM_SHADERUTILS_H
#define GLDEMOPLATFORM_SHADERUTILS_H

#include <string>

class ShaderUtils {
public:
    static std::string readShaderSource(std::string filePath);
    static std::string getShaderAbsPath(const char* fileName);
};

#define GL_GET_SHADER_SOURCE(shaderName, glslName)  \
    std::string shaderName##Str = ShaderUtils::readShaderSource(ShaderUtils::getShaderAbsPath(glslName)); \
    const char* shaderName##Source = shaderName##Str.c_str();                                             \

#endif //GLDEMOPLATFORM_SHADERUTILS_H
