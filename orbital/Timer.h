#pragma once

#include <Engine.h>
#include <functional>

class Timer : public Component {
public:
    std::function<void(Timer*)> onEnd;

    Timer(Actor* owner, float duration, const std::function<void(Timer*)>& onEnd = nullptr);
    void Update(float deltaTime) override;

    void Start(float duration) { this->duration = duration; }

private:
    float duration = 0; // In seconds.
};
