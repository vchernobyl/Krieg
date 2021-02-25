#pragma once

#include "SDL.h"

enum ButtonState {
    None,
    Pressed,
    Released,
    Held
};

class KeyboardState {
public:
    friend class InputSystem;
    bool GetKeyValue(SDL_Scancode keyCode) const;
    ButtonState GetKeyState(SDL_Scancode keyCode) const;
private:
    const Uint8* currState;
    Uint8 prevState[SDL_NUM_SCANCODES];
};

struct InputState {
    KeyboardState Keyboard;
};

class InputSystem {
public:
    bool Initialize();
    void Shutdown();

    // Called right before SDL_PollEvents loop
    void PrepareForUpdate();

    // Called right after SDL_PollEvents loop
    void Update();

    const InputState& GetState() const { return state; }
private:
    InputState state;
};
