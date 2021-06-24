#pragma once

#include <vector>

class DebugRenderer {
public:
    static void DrawRect(int x, int y, int width, int height);
    static void DrawLine(int x1, int y1, int x2, int y2);
private:
    friend class Renderer;

    static void Draw(class Renderer* renderer);
    static std::vector<class DebugShape*> shapes;
};
