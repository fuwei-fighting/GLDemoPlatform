//
// Created by fuwei on 2023/10/30.
//

#ifndef GLDEMOPLATFORM_SHADER_H
#define GLDEMOPLATFORM_SHADER_H

#include <glad/glad.h>

#include <string>

class Shader {
public:
    Shader(const char* vertexPath, const char* fragmentPath);

    void use() {
        glUseProgram(ID);
    };
    void setBool(const std::string& name, bool value) const {
        glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
    };
    void setInt(const std::string& name, int value) const {
        glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
    };
    void setFloat(const std::string& name, float value) const {
        glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
    };

public:
    unsigned int ID;

private:
    void checkCompileErrors(unsigned int shader, std::string type);


};


#endif //GLDEMOPLATFORM_SHADER_H
