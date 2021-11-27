#include "HUD.h"
#include "Game.h"
#include "Font.h"
#include "Ship.h"
#include "Weapon.h"

#include <cassert>
#include <string>

HUD::HUD(Game* game) : UIScreen(game) {
    font = game->GetFont("data/fonts/SourceCodePro-Regular.otf", 22);
}

void HUD::Draw(class SpriteBatch& batch) {
    auto player = game->GetActorByTag("Player");
    assert(player);

    auto ship = dynamic_cast<Ship*>(player);
    assert(ship);

    auto weapons = ship->GetWeapons();
    for (size_t i = 0; i < weapons.size(); i++) {
        auto name = weapons[i]->GetWeaponName();
        auto stacks = weapons[i]->GetWeaponStacks();
        auto text = name + " " + std::to_string(stacks) + "x";
        auto color = ship->GetSelectedWeapon() == weapons[i] ? Color::Yellow : Color::White;
        font->Draw(batch, text, anchor + (step * i), color);
    }
}
