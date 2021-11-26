#pragma once

#include "UIScreen.h"
#include "Math.h"

class DebugUI : public UIScreen{
public:
    DebugUI(class Game* game);
    void Draw(class SpriteBatch& batch) override;
private:
    float totalDeltaTime = 0.0f;
    float minFPS = Math::Infinity;
    int frame = 0;
    int sampleRate = 30;
};
