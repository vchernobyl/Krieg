#include "Component.h"
#include "Actor.h"
#include "InputSystem.h"
#include "Game.h"
#include "Renderer.h"

Component::Component(Actor* owner, int updateOrder)
    : owner(owner),
      updateOrder(updateOrder) {
    owner->AddComponent(this);
}

Component::~Component() {
    owner->RemoveComponent(this);
}

DrawableComponent::DrawableComponent(Actor* owner, int drawOrder)
    : Component(owner, drawOrder),
      drawOrder(drawOrder) {
    owner->GetGame()->GetRenderer()->AddDrawable(this);
}

DrawableComponent::~DrawableComponent() {
    owner->GetGame()->GetRenderer()->RemoveDrawable(this);
}
