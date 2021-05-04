#pragma once

class AudioSystem;

class SoundEvent {
public:
    SoundEvent() {}
protected:
    friend AudioSystem;
    SoundEvent(AudioSystem* system, unsigned int id) {}
private:
    unsigned int ID;
};
