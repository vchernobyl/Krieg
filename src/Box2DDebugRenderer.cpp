#include "Box2DDebugRenderer.h"
#include "DebugRenderer.h"

Box2DDebugRenderer::Box2DDebugRenderer() : b2Draw() {
    SetFlags(e_aabbBit);
};

void Box2DDebugRenderer::DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) {
    for (int32 i = 0; i < vertexCount; i += 4) {
	b2Vec2 v1 = vertices[i];
	b2Vec2 v2 = vertices[i + 1];
	b2Vec2 v3 = vertices[i + 2];
	b2Vec2 v4 = vertices[i + 3];
	DebugRenderer::DrawLine(v1.x, v1.y, v2.x, v2.y);
	DebugRenderer::DrawLine(v2.x, v2.y, v3.x, v3.y);
	DebugRenderer::DrawLine(v3.x, v3.y, v4.x, v4.y);
	DebugRenderer::DrawLine(v4.x, v4.y, v1.x, v1.y);
    }
}
