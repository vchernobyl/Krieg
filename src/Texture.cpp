#include "Texture.h"

#include <SDL.h>
#include <SDL_image.h>

Texture::Texture() : width(0), height(0), texture(nullptr) {}

void Texture::SetColor(const Vector3& color) {
    SDL_SetTextureColorMod(texture, color.x, color.y, color.z);
}

void Texture::SetColor(const Vector4& color) {
    SDL_SetTextureAlphaMod(texture, color.w);
    SDL_SetTextureColorMod(texture, color.x, color.y, color.z);
}

bool Texture::Load(const std::string& fileName, SDL_Renderer* renderer) {
    SDL_Surface* surf = IMG_Load(fileName.c_str());
    if (!surf) {
	SDL_Log("Failed to load texture file %s", fileName.c_str());
	return false;
    }

    texture = SDL_CreateTextureFromSurface(renderer, surf);
    SDL_FreeSurface(surf);
    if (!texture) {
	SDL_Log("Failed to convert surface to texture for %s", fileName.c_str());
	return false;
    }

    return true;
}

void Texture::Unload() {
    SDL_DestroyTexture(texture);
}
