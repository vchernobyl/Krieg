#include "DebugRenderer.h"

#include <glew.h>

std::vector<std::pair<DebugShape*, Vector4>> DebugRenderer::shapes = {};

void DebugRenderer::DrawRect(float x, float y, float width, float height, Vector4 color) {
}

void DebugRenderer::DrawLine(float x1, float y1, float x2, float y2, Vector4 color) {
}

void DebugRenderer::DrawCircle(float centerX, float centerY, float radius, Vector4 color) {
}

void DebugRenderer::Draw(Shader* shader) {
    glDrawElements(GL_LINES, 2, GL_UNSIGNED_INT, nullptr);
}
