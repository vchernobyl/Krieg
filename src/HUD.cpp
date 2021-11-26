#include "HUD.h"
#include "Game.h"
#include "Font.h"

HUD::HUD(Game* game) : UIScreen(game) {
    font = game->GetFont("data/fonts/uni0553.ttf", 22);
}

void HUD::Draw(class SpriteBatch& batch) {
    font->Draw(batch, "Rocket Launcher x3", Vector2(-10.5f, -7.55f));
    font->Draw(batch, "Turret x2", Vector2(-10.5f, -7.15f));
}
