#pragma once

#include <vector>

class DebugRenderer {
public:
    static void DrawRect(const class Rectangle& rect);
private:
    friend class Renderer;

    static void Draw(class Renderer* renderer);
    static std::vector<Rectangle> rects;
};
