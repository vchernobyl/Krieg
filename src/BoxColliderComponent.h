#pragma once

#include "ColliderComponent.h"

class BoxColliderComponent : public ColliderComponent {
public:
    BoxColliderComponent(Actor* owner);
    
    Manifold Intersects(ColliderComponent* other) override;
    void ResolveOverlap(const Manifold& manifold) override;

    void SetCollidable(const SDL_Rect& collidable) { this->collidable = collidable; }
    const SDL_Rect& GetCollidable() const { return collidable; }
private:
    SDL_Rect collidable;
};
