#pragma once

#include "SpriteComponent.h"
#include <string>
#include <vector>

class TileSet {
public:
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

class TileMapComponent : public SpriteComponent {
public:
    TileMapComponent(Actor* owner, TileSet& tileSet, int drawOrder = 100);
    void Draw(SDL_Renderer* renderer) override;
    void LoadMap(const std::string& mapFile);
    void SetScrollSpeed(float scrollSpeed) { this->scrollSpeed = scrollSpeed; }
private:
    TileSet tileSet;
    int tileWidth;
    int tileHeight;
    std::vector<std::vector<int> > tiles;
    float scrollSpeed;
};
