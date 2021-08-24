#pragma once

#include "Math.h"

#include <vector>
#include <utility>

class DebugRenderer {
public:
    static void DrawRect(float x, float y, float width, float height, Vector4 color);
    static void DrawLine(float x1, float y1, float x2, float y2, Vector4 color);
    static void DrawCircle(float centerX, float centerY, float radius, Vector4 color);
private:
    friend class Renderer;

    static void Draw(class Shader* shader);
    static std::vector<std::pair<class DebugShape*, Vector4>> shapes;
};
