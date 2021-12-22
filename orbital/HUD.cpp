#include "HUD.h"

HUD::HUD(Game* game) : UIScreen(game) {
    font = game->GetFont("data/fonts/SourceCodePro-Regular.otf", 22);
}

void HUD::Draw(SpriteBatch& batch) {
    font->Draw(batch, "Health: " + std::to_string(health), Vector2(8.0f, 7.2f));
}
