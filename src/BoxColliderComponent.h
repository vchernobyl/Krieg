#pragma once

#include "ColliderComponent.h"

class BoxColliderComponent : public ColliderComponent {
public:
    BoxColliderComponent(Actor* owner);
    
    CollisionInfo Intersects(ColliderComponent* other) override;
    void ResolveOverlap(const CollisionInfo& info) override;

    void SetBox(const SDL_Rect& box) { this->box = box; }
    const SDL_Rect& GetBox() const { return box; }
private:
    SDL_Rect box;
};
