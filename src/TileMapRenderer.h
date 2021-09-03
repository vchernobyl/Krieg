#pragma once

#include "TileMap.h"
#include "Shader.h"
#include "VertexArray.h"

class TileMapRenderer {
public:
    TileMapRenderer(TileMap tileMap);
    void Draw();
private:
    TileMap tileMap;
    int tileWidth;
    int tileHeight;

    Shader spriteShader;
    VertexArray spriteVertices;
};
