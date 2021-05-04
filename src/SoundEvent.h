#pragma once

class SoundEvent {
public:
    SoundEvent() {}
protected:
    friend class AudioSystem;
private:
    unsigned int ID;
};
