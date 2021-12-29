#include "OrbitalGame.h"
#include "Player.h"
#include "Planet.h"
#include "Powerups.h"
#include "HUD.h"
#include "Powerups.h"

void OrbitalGame::LoadContent() {
    auto audioSystem = GetAudioSystem();
    audioSystem->LoadBank("data/audio/Master.strings.bank");
    audioSystem->LoadBank("data/audio/Master.bank");
    
    auto player = new Player(this);
    new HUD(this, player);
    new Planet(this, Vector2::Zero, 10.0f);
    new DebugUI(this);

    GetRenderer()->SetClearColor(Color::Gray);

    auto a = new Actor(this);
    a->SetPosition(Vector2(5, 5));

    new Heart(this, Vector2::One);

    // // Animations
    // {
    //     auto idle = new Animation;
    //     idle->AddFrame(99, 0, 0, 64, 64, 0.5f);
    //     idle->AddFrame(99, 64, 0, 64, 64, 0.5f);
    //     idle->AddFrame(99, 64 * 2, 0, 64, 64, 0.5f);

    //     auto sheet = GetRenderer()->GetTexture("data/textures/animation.png");
    //     auto animation = new SpriteAnimation(a, sheet);
    //     animation->AddAnimation("idle", idle);
    // }
}
