#pragma once

#include <vector>
#include <memory>

// TODO: This should be declared privately within the DebugRenderer.
// Should be hidden from anything else. Can we move these to cpp file?
class DebugShape {
public:
    virtual ~DebugShape() {}
    virtual void Draw(class SDL_Renderer* renderer, const class Vector2& camPos) = 0;
};

class DebugRect : public DebugShape {
public:
    DebugRect(int x, int y, int width, int height);
    void Draw(class SDL_Renderer* renderer, const class Vector2& camPos) override;
private:
    int x, y;
    int width, height;
};

class DebugLine : public DebugShape {
public:
    DebugLine(int x1, int y1, int x2, int y2);
    void Draw(class SDL_Renderer* renderer, const class Vector2& camPos) override;
private:
    int x1, y1;
    int x2, y2;
};

class DebugRenderer {
public:
    static void DrawRect(int x, int y, int width, int height);
    static void DrawLine(int x1, int y1, int x2, int y2);
private:
    friend class Renderer;

    static void Draw(class Renderer* renderer);
    static std::vector<DebugShape*> shapes;
};
