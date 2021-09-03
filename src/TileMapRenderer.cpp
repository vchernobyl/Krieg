#include "TileMapRenderer.h"

TileMapRenderer::TileMapRenderer(TileMap tileMap) : tileMap(tileMap) {
    const auto tileSet = tileMap.GetTileSets().front();
    tileWidth = tileSet.GetTileWidth();
    tileHeight = tileSet.GetTileHeight();

    spriteShader.Load("data/shaders/Sprite.vert", "data/shaders/Sprite.frag");
    spriteShader.SetActive();
    spriteShader.SetMatrixUniform("uViewProjection", Matrix4::CreateSimpleViewProjection(1024, 768));

    const float vertices[] = {
	-0.5f, 0.5f, 0.0f, 0.0f, 0.0f, // top left
 	0.5f, 0.5f, 0.0f, 1.0f, 0.0f,  // top right
	0.5f, -0.5f, 0.0f, 1.0f, 1.0f, // bottom right
	-0.5f, -0.5f, 0.0, 0.0f, 1.0f  // bottom left
    };

    const unsigned int indices[] = {
	0, 1, 2,
	2, 3, 0
    };

    spriteVertices = VertexArray(vertices, 4, indices, 6);
}

void TileMapRenderer::Draw() {
    spriteShader.SetActive();
    
    for (auto layer : tileMap.GetLayers()) {
	for (auto tile : layer.tiles) {
	    auto tileInfo = tile.tileInfo;
	    auto src = Rectangle(tileInfo.source.position, tileInfo.source.size);
	    auto dst = Rectangle(tile.position, Vector2(tileWidth, tileHeight));

            // TODO: Pass sample source rectangle.

            // TODO: Pass world position uniform.
	    
	    // TODO: Draw a single tile.
	}
    }
}
