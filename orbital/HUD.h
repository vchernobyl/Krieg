#pragma once

#include <Engine.h>

class HUD : public UIScreen {
public:
    HUD(Game* game);
    void Draw(SpriteBatch& batch) override;
    
    void SetHealth(int health) { this->health = health; }

private:
    int health;
    
    Vector2 anchor;
    Font* font;
};
