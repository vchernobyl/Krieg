#pragma once

#include <vector>

class DebugRenderer {
public:
    static void DrawRect(float x, float y, float width, float height);
    static void DrawLine(float x1, float y1, float x2, float y2);
private:
    friend class Renderer;

    static void Draw(class Renderer* renderer);
    static std::vector<class DebugShape*> shapes;
};
