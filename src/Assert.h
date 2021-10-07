#include <glew.h>

static void GLClearError() {
    while (glGetError() != GL_NO_ERROR);
}

static void GLCheckError() {
    while (GLEnum error = glGetError()) {
	std::printf("[OpenGL error] %d", error);
    }
}
