#pragma once

#include <vector>
#include <utility>

struct Color {
    uint8_t r, g, b, a;
};    

class DebugRenderer {
public:
    static void DrawRect(float x, float y, float width, float height, Color color);
    static void DrawLine(float x1, float y1, float x2, float y2, Color color);
private:
    friend class Renderer;

    static void Draw(class Renderer* renderer);
    static std::vector<std::pair<class DebugShape*, Color>> shapes;
};
