#include "DebugUI.h"
#include "Game.h"
#include "Font.h"
#include <string>
#include <SDL/SDL.h>

DebugUI::DebugUI(Game* game) : UIScreen(game) {
    font = game->GetFont("data/fonts/uni0553.ttf", 32);
};

void DebugUI::Draw(SpriteBatch& batch) {
    // FPS.
    auto fps = static_cast<int>(1.0f / game->GetDeltaTime());
    auto text = "FPS: " + std::to_string(fps);
    font->Draw(batch, text, Vector2(-10.5f, 7.5f));

    // Draw calls.
    
}
