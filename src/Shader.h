#pragma once

#include <GL/glew.h>
#include <string>
#include "Maths.h"

class Shader {
public:
    Shader();
    bool Load(const std::string& vertName, const std::string& fragName);
    void Unload();
    void SetActive();
    void SetMatrixUniform(const char* name, const Matrix4& matrix);

private:
    bool CompileShader(const std::string& fileName, GLenum shaderType, GLuint& outShader);
    bool IsCompiled(GLuint shader);
    bool IsValidProgram();

    GLuint vertexShader = 0;
    GLuint fragmentShader = 0;
    GLuint shaderProgram = 0;
};
