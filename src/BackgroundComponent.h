#pragma once

#include "SpriteComponent.h"

class BackgroundComponent : public SpriteComponent {
public:
    BackgroundComponent(Actor* owner, int updateOrder = 10);
    void Draw(SDL_Renderer* renderer) override;
};
