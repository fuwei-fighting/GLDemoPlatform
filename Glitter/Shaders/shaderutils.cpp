//
// Created by fuwei on 2023/10/28.
//

#include "shaderutils.h"

#include <fstream>

using namespace std;

std::string ShaderUtils::readShaderSource(std::string filePath) {
    string content;
    ifstream fileStream(filePath, ios::in);
    if (!fileStream.good()) {
        return "";
    }
    string line = "";
    while (!fileStream.eof()) {
        getline(fileStream, line);
        content.append(line + "\n");
    }
    fileStream.close();
    return content;
}

std::string ShaderUtils::getShaderAbsPath(const char* fileName) {
    return std::string(PROJECT_SOURCE_DIR) + "/Glitter/Shaders/" + fileName + ".glsl";
}