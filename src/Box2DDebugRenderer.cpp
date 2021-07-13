#include "Box2DDebugRenderer.h"
#include "DebugRenderer.h"

Box2DDebugRenderer::Box2DDebugRenderer() : b2Draw() {
    SetFlags(e_shapeBit);
};

void Box2DDebugRenderer::DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) {
    for (int32 i = 0; i < vertexCount - 1; i++) {
	const b2Vec2 v1 = vertices[i];
	const b2Vec2 v2 = vertices[i + 1];
	DebugRenderer::DrawLine(v1.x, v1.y, v2.x, v2.y);
    }

    const b2Vec2 first = vertices[0];
    const b2Vec2 last = vertices[vertexCount - 1];
    DebugRenderer::DrawLine(first.x, first.y, last.x, last.y);
}
