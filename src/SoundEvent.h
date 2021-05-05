#pragma once

#include <string>

class AudioSystem;

class SoundEvent {
public:
    SoundEvent();
    bool IsValid();
    void Restart();
    void Stop(bool allowFadeOut = true);

    void SetPaused(bool pause);
    void SetVolume(float value);
    void SetPitch(float value);
    void SetParameter(const std::string& name, float value);

    bool GetPaused() const;
    float GetVolume() const;
    float GetPitch() const;
    float GetParameter(const std::string& name) const;
protected:
    friend AudioSystem;
    SoundEvent(AudioSystem* system, unsigned int id);
private:
    AudioSystem* system;
    unsigned int ID;
};
