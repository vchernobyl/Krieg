#pragma once

#include "UIScreen.h"

class DebugUI : public UIScreen{
public:
    DebugUI(class Game* game);
    void Draw(class SpriteBatch& batch) override;
private:
};
