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


#endif //GLDEMOPLATFORM_SHADERUTILS_H
