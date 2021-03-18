#pragma once

#include "ColliderComponent.h"
#include "Actor.h"

class BoxColliderComponent : public ColliderComponent {
public:
    BoxColliderComponent(Actor* owner);
    
    Manifold Intersects(ColliderComponent* other) override;
    void ResolveOverlap(const Manifold& manifold) override;

    void SetCollidable(const SDL_Rect& collidable);
    const SDL_Rect& GetCollidable();
private:
    void SetPosition();
    SDL_Rect collidable;
};
