#include "Shader.h"
#include "Assert.h"

#include <SDL.h>
#include <fstream>
#include <sstream>

Shader::Shader() {}

bool Shader::Load(const std::string& vertName, const std::string& fragName) {
    if (!CompileShader(vertName, GL_VERTEX_SHADER, vertexShader) ||
	!CompileShader(fragName, GL_FRAGMENT_SHADER, fragmentShader)) {
	return false;
    }

    GL_CALL(shaderProgram = glCreateProgram());
    GL_CALL(glAttachShader(shaderProgram, vertexShader));
    GL_CALL(glAttachShader(shaderProgram, fragmentShader));
    GL_CALL(glLinkProgram(shaderProgram));

    if (!IsValidProgram()) {
	return false;
    }

    return true;
}

void Shader::Unload() {
    GL_CALL(glDeleteProgram(shaderProgram));
    GL_CALL(glDeleteShader(vertexShader));
    GL_CALL(glDeleteShader(fragmentShader));
}

void Shader::SetActive() {
    GL_CALL(glUseProgram(shaderProgram));
}

void Shader::SetMatrixUniform(const char* name, const Matrix4& matrix) {
    GL_CALL(GLuint loc = glGetUniformLocation(shaderProgram, name));
    GL_CALL(glUniformMatrix4fv(loc, 1, GL_TRUE, matrix.GetAsFloatPtr()));
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
	GL_CALL(outShader = glCreateShader(shaderType));
	GL_CALL(glShaderSource(outShader, 1, &(contentsChar), nullptr));
	GL_CALL(glCompileShader(outShader));

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
    GL_CALL(glGetShaderiv(shader, GL_COMPILE_STATUS, &status));

    if (status != GL_TRUE) {
	char buffer[512];
	memset(buffer, 0, 512);
	GL_CALL(glGetShaderInfoLog(shader, 511, nullptr, buffer));
	SDL_Log("GLSL compilation failed:\n%s", buffer);
	return false;
    }
    
    return true;
}

bool Shader::IsValidProgram() {
    GLint status;
    GL_CALL(glGetProgramiv(shaderProgram, GL_LINK_STATUS, &status));

    if (status != GL_TRUE) {
	char buffer[512];
	memset(buffer, 0, 512);
	GL_CALL(glGetProgramInfoLog(shaderProgram, 511, nullptr, buffer));
	SDL_Log("GLSL linking failed:\n%s", buffer);
	return false;
    }
    
    return true;
}
