#include "TileSet.h"

TileSet::TileSet() : texture(nullptr), rows(0), cols(0), tileWidth(0), tileHeight(0) {}

TileSet::TileSet(SDL_Texture* texture, int rows, int cols)
    : texture(texture), rows(rows), cols(cols) {
    int textureWidth, textureHeight;
    SDL_QueryTexture(texture, nullptr, nullptr, &textureWidth, &textureHeight);
    tileWidth = textureWidth / cols;
    tileHeight = textureHeight / rows;
}

const SDL_Rect TileSet::GetTile(int id) const {
    const int row = id / rows;
    const int col = id % rows;
    return SDL_Rect { col * tileWidth, row * tileHeight, tileWidth, tileHeight };
}
