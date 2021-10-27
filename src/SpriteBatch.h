#pragma once

#include "Math.h"
#include <GL/glew.h>
#include <vector>

struct Vertex {
    Vector2 position;
    Vector4 color;
    Vector2 uv;

    void SetPosition(float x, float y) { position = Vector2(x, y); }
    void SetColor(float r, float g, float b, float a) { color = Vector4(r, g, b, a); }
    void SetUV(float u, float v) { uv = Vector2(u, v); }
};

class SpriteBatchItem {
public:
    SpriteBatchItem(const Vector4& destRect, const Vector4& uvRect,
		    GLuint texture, int depth, const Vector4& color);

    SpriteBatchItem(const Vector4& destRect, const Vector4& uvRect,
		    GLuint texture, int depth, const Vector4& color, float angle);
    
    GLuint texture;
    int depth;
    Vertex topLeft;
    Vertex bottomLeft;
    Vertex bottomRight;
    Vertex topRight;
};

class RenderBatch {
public:
    RenderBatch(GLuint offset, GLuint numVertices, GLuint texture) :
	offset(offset), numVertices(numVertices), texture(texture) {}
    
    GLuint offset;
    GLuint numVertices;
    GLuint texture;
};

class SpriteBatch {
public:
    enum class SortType {
	None,
	FrontToBack,
	BackToFront,
	Texture
    };

    SpriteBatch();
    void Initialize();
    void Begin(SortType sortType = SortType::Texture);
    void End();

    void Draw(const Vector4& destRect, const Vector4& uvRect,
	      GLuint texture, int depth, const Vector4& color);

    void Draw(const Vector4& destRect, const Vector4& uvRect,
	      GLuint texture, int depth, const Vector4& color, float angle);

    void Draw(const Vector4& destRect, const Vector4& uvRect,
	      GLuint texture, int depth, const Vector4& color, const Vector2& direction);

    void DrawBatch();

private:
    void CreateRenderBatches();
    void CreateVertexArray();
    void SortSpriteBatchItems();

    GLuint vbo = 0;
    GLuint vao = 0;
    SortType sortType = SortType::Texture;

    std::vector<SpriteBatchItem*> spriteBatchItemPtrs;
    std::vector<SpriteBatchItem> spriteBatchItems;
    std::vector<RenderBatch> renderBatches;
};
