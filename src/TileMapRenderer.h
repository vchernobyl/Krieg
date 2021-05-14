#pragma once

// TODO: Move this guy to the TileMap header.
class TileMapRenderer {
public:
    TileMapRenderer(class TileMap* map);
    void Draw(class Renderer* renderer);
private:
    class TileMap* map;
};
