#pragma once

#include <Engine.h>

class HUD : public UIScreen {
public:
    HUD(Game* game, class Player* player);
    void Draw(SpriteBatch& batch) override;
private:
    Vector2 anchor;
    Font* font;
    class Health* health = nullptr;
};
