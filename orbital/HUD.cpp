#include "HUD.h"
#include "Player.h"
#include "Health.h"

HUD::HUD(Game* game, Player* player) : UIScreen(game) {
    font = game->GetFont("data/fonts/SourceCodePro-Regular.otf", 18);
    health = player->GetComponent<Health>();
}

void HUD::Draw(SpriteBatch& batch) {
    int healthAmount = (health == nullptr) ? 0 : health->GetHealth();
    font->Draw(batch, "Health: " + std::to_string(healthAmount), Vector2(8.0f, 7.2f));
}
