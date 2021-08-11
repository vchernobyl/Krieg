#include "Shader.h"

#include <SDL.h>
#include <fstream>
#include <sstream>

bool Shader::Load(const std::string& vertName, const std::string& fragName) {
    if (!CompileShader(vertName, GL_VERTEX_SHADER, vertexShader) ||
	!CompileShader(fragName, GL_FRAGMENT_SHADER, fragmentShader)) {
	return false;
    }

    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    if (!IsValidProgram()) {
	return false;
    }

    return true;
}

void Shader::Unload() {
    glDeleteProgram(shaderProgram);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void Shader::SetActive() {
    glUseProgram(shaderProgram);
}

bool Shader::CompileShader(const std::string& fileName, GLenum shaderType, GLuint& outShader) {
    std::ifstream shaderFile(fileName);
    if (shaderFile.is_open()) {
	// Read the contents of the shader source file into a string.
	std::stringstream sstream;
	sstream << shaderFile.rdbuf();
	std::string contents = sstream.str();
	const char* contentsChar = contents.c_str();

	// Create a shader of the specified type. In our case either vertex or fragment shader.
	outShader = glCreateShader(shaderType);
	glShaderSource(outShader, 1, &(contentsChar), nullptr);
	glCompileShader(outShader);

	if (!IsCompiled(outShader)) {
	    SDL_Log("Failed to compile shader: %s", fileName.c_str());
	    return false;
	}
    } else {
	SDL_Log("Shader file not found: %s", fileName.c_str());
	return false;
    }

    return true;
}

bool Shader::IsCompiled(GLuint shader) {
    GLint status;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);

    if (status != GL_TRUE) {
	char buffer[512];
	memset(buffer, 0, 512);
	glGetShaderInfoLog(shader, 511, nullptr, buffer);
	SDL_Log("GLSL compilation failed:\n%s", buffer);
	return false;
    }
    
    return true;
}

bool Shader::IsValidProgram() {
    GLint status;
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &status);

    if (status != GL_TRUE) {
	char buffer[512];
	memset(buffer, 0, 512);
	glGetProgramInfoLog(shaderProgram, 511, nullptr, buffer);
	SDL_Log("GLSL linking failed:\n%s", buffer);
	return false;
    }
    
    return true;
}
