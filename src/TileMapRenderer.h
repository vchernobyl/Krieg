#pragma once

class TileMapRenderer {
public:
    TileMapRenderer(class TileMap* map);
    void Draw(class Renderer* renderer);
private:
    class TileMap* map;
};
