#pragma once

#include "SDL.h"

class TileSet {
public:
    TileSet();
    TileSet(SDL_Texture* texture, int rows, int cols);
    SDL_Texture* GetTexture() const { return texture; }
    const SDL_Rect GetTile(int id) const;
    int GetTileWidth() const { return tileWidth; }
    int GetTileHeight() const { return tileHeight; }
private:
    SDL_Texture* texture;
    int rows, cols;
    int tileWidth, tileHeight;
};
