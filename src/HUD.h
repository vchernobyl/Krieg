#pragma once

#include "UIScreen.h"

class HUD : public UIScreen {
public:
    HUD(class Game* game);
    void Draw(class SpriteBatch& batch) override;
private:
    std::vector<class Weapon*> weapons;
};
