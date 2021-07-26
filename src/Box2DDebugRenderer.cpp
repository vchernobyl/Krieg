#include "Box2DDebugRenderer.h"
#include "DebugRenderer.h"

Box2DDebugRenderer::Box2DDebugRenderer() : b2Draw() {
    SetFlags(e_shapeBit | e_centerOfMassBit);
};

void Box2DDebugRenderer::DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) {
    const auto c = Vector4(color.r * 255, color.g * 255, color.b * 255, color.a * 255);
    
    for (int32 i = 0; i < vertexCount - 1; i++) {
	const auto v1 = vertices[i];
	const auto v2 = vertices[i + 1];
	DebugRenderer::DrawLine(v1.x, v1.y, v2.x, v2.y, c);
    }

    const auto first = vertices[0];
    const auto last = vertices[vertexCount - 1];
    DebugRenderer::DrawLine(first.x, first.y, last.x, last.y, c);
}

void Box2DDebugRenderer::DrawTransform(const b2Transform& xf) {
    const auto color = Vector4(255, 0, 0, 255);
    DebugRenderer::DrawRect(xf.p.x, xf.p.y, 0.085f, 0.085f, color);
}

void Box2DDebugRenderer::DrawSolidCircle(const b2Vec2& center, float radius, const b2Vec2& axis, const b2Color& color) {
    const auto c = Vector4(color.r * 255, color.g * 255, color.b * 255, color.a * 255);
    DebugRenderer::DrawCircle(center.x, center.y, radius, c);
}
