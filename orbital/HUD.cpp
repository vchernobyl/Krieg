#include "HUD.h"
#include "Player.h"
#include "Health.h"

HUD::HUD(Game* game, Player* player) : UIScreen(game), player(player) {
    font = game->GetFont("data/fonts/SourceCodePro-Regular.otf", 18);
}

void HUD::Draw(SpriteBatch& batch) {
    int health = 0;
    if (auto player = game->GetActorByTag("Player")) {
        health = player->GetComponent<Health>()->GetHealth();
    }
    font->Draw(batch, "Health: " + std::to_string(health), Vector2(8.0f, 7.2f));
}
