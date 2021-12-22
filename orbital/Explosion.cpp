#include "Explosion.h"

Explosion::Explosion(Game* game, const Vector2& position) : Actor(game) {
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

    auto audio = new AudioComponent(this);
    audio->PlayEvent("event:/Rocket_Explosion");
}

void Explosion::UpdateActor(float deltaTime) {
    time += deltaTime;
    if (time >= lifeTime) {
        SetState(State::Dead);
    }
}
