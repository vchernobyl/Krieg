#include "Texture.h"
#include "Assert.h"

#include <SOIL/SOIL.h>
#include <SDL.h>
#include <GL/glew.h>

bool Texture::Load(const std::string& fileName) {
    int channels = 0;
    unsigned char* image = SOIL_load_image(fileName.c_str(), &width, &height, &channels, SOIL_LOAD_AUTO);

    if (image == nullptr) {
	SDL_Log("SOIL failed to load image %s: %s", fileName.c_str(), SOIL_last_result());
	return false;
    }

    int format = GL_RGB;
    if (channels == 4) {
	format = GL_RGBA;
    }

    GL_CALL(glGenTextures(1, &textureID));
    GL_CALL(glBindTexture(GL_TEXTURE_2D, textureID));
    GL_CALL(glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, image));

    SOIL_free_image_data(image);

    // Enable bilinear filtering.
    // TODO: For pixelated look use GL_NEAREST instead.
    GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
    GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));

    GL_CALL(glGenerateMipmap(GL_TEXTURE_2D));

    return true;
}

void Texture::Unload() {
    GL_CALL(glDeleteTextures(1, &textureID));
}

void Texture::SetActive() {
    GL_CALL(glBindTexture(GL_TEXTURE_2D, textureID));
}
