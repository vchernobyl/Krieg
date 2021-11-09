#include "Damageable.h"
#include "Actor.h"
#include "SpriteComponent.h"
#include "ParticleComponent.h"
#include "Random.h"
#include "Game.h"
#include "Renderer.h"
#include "Texture.h"

Damageable::Damageable(Actor* owner, int health) : Component(owner), health(health) {
    ownerSprite = owner->GetComponent<SpriteComponent>();
    originalColor = ownerSprite->GetColor();

    particleEmitter = new ParticleComponent(owner);
    auto texture = owner->GetGame()->GetRenderer()->GetTexture("data/textures/Particle.png");
    particleEmitter->SetTexture(texture);
}

void Damageable::Update(float deltaTime) {
    if (shouldFlash) {
        ownerSprite->SetColor(Color::Red);
        flashFrames--;
        if (flashFrames <= 0) {
            shouldFlash = false;
            ownerSprite->SetColor(originalColor);
        }
    } 
}

void Damageable::Damage(int amount) {
    shouldFlash = true;
    flashFrames = 8;
    health -= amount;

    ParticleProps props;
    props.position = owner->GetPosition();
    props.velocity = Random::GetVector(Vector2(-1.0f, -1.0f), Vector2(1.0f, 1.0f));
    props.velocityVariation = Vector2(0.5f, 0.5f);
    props.colorBegin = Color::White;
    props.colorEnd = Color::White;
    props.sizeBegin = 0.15f;
    props.sizeEnd = 0.0f;
    props.sizeVariation = 0.0f;
    props.rotationBegin = 0.0f;
    props.rotationSpeed = 2.0f;
    props.lifeTime = 1.5f;

    particleEmitter->Emit(props, 15);

    if (health <= 0) {
        GetOwner()->SetState(Actor::State::Dead);
    }
}
