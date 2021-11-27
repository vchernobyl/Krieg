#pragma once

#include "UIScreen.h"

class HUD : public UIScreen {
public:
    HUD(class Game* game);
    void Draw(class SpriteBatch& batch) override;
private:
    Vector2 anchor = Vector2(-10.5f, -7.55f);
    Vector2 step = Vector2(0.0f, 0.40f);
};
