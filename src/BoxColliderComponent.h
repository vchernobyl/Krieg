#pragma once

#include "ColliderComponent.h"
#include "SDL.h"
#include "Math.h"

class BoxColliderComponent : public ColliderComponent {
public:
    BoxColliderComponent(class Actor* owner);
    ~BoxColliderComponent();
    
    Manifold Intersects(ColliderComponent* other) override;
    void ResolveOverlap(const Manifold& manifold) override;

    void SetCollidable(const SDL_Rect& collidable);
    const SDL_Rect& GetCollidable();
private:
    void SetPosition();
    SDL_Rect collidable;
    Vector2 offset;
};
