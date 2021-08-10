#pragma once

#include <glew.h>
#include <string>

class Shader {
public:
    Shader();
    ~Shader();

    bool Load(const std::string& vertName, const std::string& fragName);
    void SetActive();

private:
    bool CompileShader(const std::string& fileName, GLenum shaderType, GLuint& outShader);
    bool IsCompiled(GLuint shader);
    bool IsValidProgram();

    GLuint vertexShader;
    GLuint fragmentShader;
    GLuint shaderProgram;
};
