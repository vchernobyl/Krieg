#pragma once

#include "SpriteComponent.h"

class BackgroundComponent : public SpriteComponent {
public:
    BackgroundComponent(Actor* owner, int updateOrder = 10);
    void ProcessInput(const InputState& input) override;
    void Draw(SDL_Renderer* renderer) override;
private:
    SDL_Rect camera;
    SDL_Rect background;
};
