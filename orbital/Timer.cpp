#include "Timer.h"

Timer::Timer(Actor* owner, float duration, const std::function<void(Timer*)>& onEnd)
    : Component(owner), duration(duration), onEnd(onEnd) {
}

void Timer::Update(float deltaTime) {
    if (duration > 0.0f) {
        duration -= deltaTime;
        if (duration <= 0.0f && onEnd) {
            onEnd(this);
        }
    }
}
