#pragma once

#include <Engine.h>

class Hud : public UIScreen {
public:
    Hud(Game* game);
    void Draw(SpriteBatch& batch) override;
    
    void SetHealth(int health) { this->health = health; }
    void SetScore(int score) { this->score = score; }

private:
    int health = 0;
    int score = 0;

    Vector2 anchor;
    Font* font;
};
