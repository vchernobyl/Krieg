#pragma once

#include "Math.h"
#include <SDL/SDL.h>

enum class ButtonState {
    None,
    Pressed,
    Released,
    Held
};

class KeyboardState {
public:
    friend class InputSystem;
    bool GetKeyValue(SDL_Scancode keyCode) const; // TODO: Rename this to IsKeyPressed(..).
    ButtonState GetKeyState(SDL_Scancode keyCode) const;
private:
    const Uint8* currState;
    Uint8 prevState[SDL_NUM_SCANCODES];
};

class MouseState {
public:
    friend class InputSystem;
    const Vector2& GetPosition() const { return mousePosition; }
    bool IsButtonPressed(int button) const;
    ButtonState GetButtonState(int button) const;
private:
    Vector2 mousePosition;
    Uint32 currButtons;
    Uint32 prevButtons;
};

struct InputState {
    KeyboardState Keyboard;
    MouseState Mouse;
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
