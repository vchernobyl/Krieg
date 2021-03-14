#include "TileSet.h"

TileSet::TileSet() : texture(nullptr), rows(0), cols(0), tileWidth(0), tileHeight(0) {}

TileSet::TileSet(SDL_Texture* texture, int tileWidth, int tileHeight)
    : texture(texture),
      tileWidth(tileWidth), tileHeight(tileHeight) {
    int textureWidth, textureHeight;
    SDL_QueryTexture(texture, nullptr, nullptr, &textureWidth, &textureHeight);
    cols = textureWidth / tileWidth;
    rows = textureHeight / tileHeight;
}

const SDL_Rect TileSet::GetTile(int id) const {
    const int row = id / cols;
    const int col = id % cols;
    return SDL_Rect { col * tileWidth, row * tileHeight, tileWidth, tileHeight };
}
