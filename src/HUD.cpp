#include "HUD.h"
#include "Game.h"
#include "Renderer.h"
#include "Texture.h"
#include "SpriteBatch.h"

HUD::HUD(Game* game) : UIScreen(game) {
    healthBar = game->GetRenderer()->GetTexture("data/textures/HealthBar.png");
    SetTitle("Title");
}

void HUD::Update(float deltaTime) {

}

void HUD::Draw(class SpriteBatch& spriteBatch) {
    DrawTexture(spriteBatch, healthBar);
}
