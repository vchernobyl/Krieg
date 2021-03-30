#pragma once

class PhysicsWorld;
class Camera;
class SDL_Renderer;

class DebugRenderer {
public:
    DebugRenderer(PhysicsWorld* world, Camera* camera) : world(world), camera(camera) {}
    void Draw(SDL_Renderer* renderer);
private:
    PhysicsWorld* world;
    Camera* camera;
};

    
    
    
