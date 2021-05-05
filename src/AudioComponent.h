#pragma once

#include "Component.h"
#include "SoundEvent.h"

#include <string>
#include <vector>

class AudioComponent : public Component {
public:
    AudioComponent(class Actor* owner, int updateOrder = 200);
    ~AudioComponent();

    void Update(float deltaTime) override;
    SoundEvent PlayEvent(const std::string& name);
    void StopAllEvents();
private:
    std::vector<SoundEvent> events;
};
