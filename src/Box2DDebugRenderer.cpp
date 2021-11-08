#include "Box2DDebugRenderer.h"
#include "DebugRenderer.h"
#include "Math.h"
#include "Game.h"

Box2DDebugRenderer::Box2DDebugRenderer() : b2Draw() {
    SetFlags(e_shapeBit | e_centerOfMassBit);
};

void Box2DDebugRenderer::DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount,
                                          const b2Color& color) {
    for (int32 i = 0; i < vertexCount - 1; i++) {
        auto from = Vector2(vertices[i].x, vertices[i].y);
        auto to = Vector2(vertices[i + 1].x, vertices[i + 1].y);
        DebugRenderer::DrawLine(from, to);
    }

    auto first = Vector2(vertices[0].x, vertices[0].y);
    auto last = Vector2(vertices[vertexCount - 1].x, vertices[vertexCount - 1].y);
    DebugRenderer::DrawLine(first, last,
                            Vector4(color.r, color.g, color.b, color.a));
}

void Box2DDebugRenderer::DrawTransform(const b2Transform& xf) {
}

void Box2DDebugRenderer::DrawSolidCircle(const b2Vec2& center, float radius,
                                         const b2Vec2& axis, const b2Color& color) {
    DebugRenderer::DrawCircle(Vector2(center.x, center.y), radius,
                              Vector4(color.r, color.g, color.b, color.a));
}
