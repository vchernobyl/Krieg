#pragma once

class DebugRenderer {
public:
    DebugRenderer(class PhysicsWorld* world) : world(world) {}
    void Draw(class Renderer* renderer);
private:
    class PhysicsWorld* world;
};
