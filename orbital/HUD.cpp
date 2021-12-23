#include "Hud.h"

Hud::Hud(Game* game) : UIScreen(game) {
    font = game->GetFont("data/fonts/SourceCodePro-Regular.otf", 18);
}

void Hud::Draw(SpriteBatch& batch) {
    font->Draw(batch, "Health: " + std::to_string(health), Vector2(8.0f, 7.2f));
    font->Draw(batch, "Score: " + std::to_string(score), Vector2(8.0f, 6.8f));
}
