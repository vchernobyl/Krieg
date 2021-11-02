#pragma once

#include "UIScreen.h"

class HUD : public UIScreen {
public:
    HUD(class Game* game);
    void Update(float deltaTime) override;
    void Draw(class SpriteBatch& spriteBatch) override;
private:
    class Texture* healthBar;
};
