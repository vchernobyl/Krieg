#include "Box2DDebugRenderer.h"
#include "DebugDraw.h"
#include "Math.h"
#include "Game.h"

Box2DDebugRenderer::Box2DDebugRenderer() : b2Draw() {
    SetFlags(e_shapeBit | e_centerOfMassBit);
};

void Box2DDebugRenderer::DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) {
    const auto width = vertices[1].x - vertices[0].x;
    const auto height = vertices[3].y - vertices[0].y;
    const auto center = Vector2(vertices[0].x + width / 2.0f, vertices[0].y + height / 2.0f);
    const auto box = Vector4(center.x, center.y, width, height);
    DebugDraw::DrawBox(box, Vector4(0, 0, 0, 0), 0);
}

void Box2DDebugRenderer::DrawTransform(const b2Transform& xf) {
}

void Box2DDebugRenderer::DrawSolidCircle(const b2Vec2& center, float radius, const b2Vec2& axis, const b2Color& color) {
}
