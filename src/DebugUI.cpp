#include "DebugUI.h"
#include "Game.h"
#include "Font.h"
#include "SpriteBatch.h"
#include <string>

DebugUI::DebugUI(Game* game) : UIScreen(game) {
    font = game->GetFont("data/fonts/SourceCodePro-Regular.otf", 19);
};

void DebugUI::Draw(SpriteBatch& batch) {
    totalDeltaTime += game->GetDeltaTime();
    auto averageDeltaTime = totalDeltaTime / (++frame);
    auto fps = 1.0f / averageDeltaTime;

    if (fps < minFPS) {
        minFPS = fps;
    }

    font->Draw(batch, "Average FPS: " + std::to_string(static_cast<int>(fps)), Vector2(-10.5f, 7.55f));
    font->Draw(batch, "Min FPS: " + std::to_string(static_cast<int>(minFPS)), Vector2(-10.5f, 7.20f));
    font->Draw(batch, "Sample rate: " + std::to_string(sampleRate), Vector2(-10.5f, 6.85f));
    font->Draw(batch, "Actors live: " + std::to_string(game->GetActors().   size()), Vector2(-10.5f, 6.5f));

    // Reset the accumulated average FPS values.
    if (frame == sampleRate) {
        totalDeltaTime = 0.0f;
        frame = 0;
    }
}
