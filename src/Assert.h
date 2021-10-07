#include <glew.h>
#include <iostream>
#include <cassert>

#define GL_CALL(x) GLClearError();\
    x;\
    assert(GLLogCall())

static void GLClearError() {
    while (glGetError() != GL_NO_ERROR);
}

static bool GLLogCall() {
    while (GLenum error = glGetError()) {
	std::printf("[OpenGL error] %d\n", error);
	return false;
    }
    return true;
}
