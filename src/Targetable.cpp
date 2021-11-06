#include "Targetable.h"
#include "Actor.h"
#include "RigidbodyComponent.h"
#include "SpriteComponent.h"
#include "Renderer.h"
#include "Texture.h"
#include "InputSystem.h"
#include "Game.h"
#include "PhysicsWorld.h"
#include "Camera.h"

Targetable::Targetable(Actor* owner) : Component(owner) {
    sprite = new SpriteComponent(owner, 300);
    sprite->SetTexture(owner->GetGame()->GetRenderer()->GetTexture("data/textures/Circle.png"));
    sprite->SetEnabled(false);
}

void Targetable::Select() {
    isSelected = !isSelected;
    sprite->SetEnabled(isSelected);
}
