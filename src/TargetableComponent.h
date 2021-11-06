#pragma once

#include "Component.h"

class TargetableComponent : public Component {
public:
    TargetableComponent(class Actor* owner);
    void ProcessInput(const struct InputState& inputState) override;
    bool IsSelected() const { return isSelected; }
private:
    class SpriteComponent* sprite = nullptr;
    bool isSelected = false;
};
