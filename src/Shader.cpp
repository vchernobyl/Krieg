#include "Shader.h"

#include <SDL.h>
#include <fstream>
#include <sstream>

Shader::Shader() {
}

Shader::~Shader() {
}

bool Shader::Load(const std::string& vertName, const std::string& fragName) {
    return false;
}

void Shader::SetActive() {
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
    return false;
}

bool Shader::IsValidProgram() {
    return false;
}
