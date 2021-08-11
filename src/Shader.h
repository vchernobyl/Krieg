#pragma once

#include <glew.h>
#include <string>

class Shader {
public:
    bool Load(const std::string& vertName, const std::string& fragName);
    void Unload();
    void SetActive();

private:
    bool CompileShader(const std::string& fileName, GLenum shaderType, GLuint& outShader);
    bool IsCompiled(GLuint shader);
    bool IsValidProgram();

    GLuint vertexShader = 0;
    GLuint fragmentShader = 0;
    GLuint shaderProgram = 0;
};
