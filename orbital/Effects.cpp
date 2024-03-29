#include "Effects.h"
#include "Timer.h"

Explosion::Explosion(Game* game, const Vector2& position, float lifeTime) : Actor(game) {
    SetPosition(position);

    auto emitter = new ParticleComponent(this);
    auto texture = game->GetRenderer()->GetTexture("data/textures/Particle.png");
    emitter->SetTexture(texture);

    ParticleProps props;
    props.velocity = Random::GetVector(Vector2(-1.0f, -1.0f), Vector2(1.0f, 1.0f));
    props.velocityVariation = Vector2(-1.0f, 1.0f);
    props.colorBegin = Color::Yellow;
    props.colorEnd = Vector4(1.0f, 0.0f, 0.0f, 0.0f);
    props.sizeBegin = 0.15f;
    props.sizeEnd = 0.0f;
    props.sizeVariation = 0.0f;
    props.rotationBegin = 0.0f;
    props.rotationSpeed = 2.0f;
    props.lifeTime = lifeTime;

    emitter->Emit(props, 35);

    new Timer(this, lifeTime, [](Timer* self) { self->GetOwner()->Destroy(); });
}

HeartPickupEffect::HeartPickupEffect(Game* game, const Vector2& position, float lifeTime)
    : Actor(game) {
    SetPosition(position);

    auto emitter = new ParticleComponent(this);
    emitter->SetTexture(game->GetRenderer()->GetTexture("data/textures/Particle.png"));

    ParticleProps props;
    props.velocity = Random::GetVector(Vector2(-1.0f, -1.0f), Vector2(1.0f, 1.0f));
    props.velocityVariation = Vector2(-1.0f, 1.0f);
    props.colorBegin = Vector4(0.0f, 0.8f, 0.1f, 0.7f);
    props.colorEnd = Vector4(0.0f, 1.0f, 0.3f, 0.0f);
    props.sizeBegin = 0.15f;
    props.sizeEnd = 0.0f;
    props.sizeVariation = 0.0f;
    props.rotationBegin = 0.0f;
    props.rotationSpeed = 2.0f;
    props.lifeTime = lifeTime;

    emitter->Emit(props, 15);

    new Timer(this, lifeTime, [](Timer* self) { self->GetOwner()->Destroy(); });
}
