#include "InputSystem.h"

bool KeyboardState::IsKeyPressed(Key key) const {
    return currState[static_cast<Uint8>(key)] == 1;
}

ButtonState KeyboardState::GetKeyState(Key key) const {
    if (prevState[static_cast<Uint8>(key)] == 0) {
        if (currState[static_cast<Uint8>(key)] == 0) {
            return ButtonState::None;
        } else {
            return ButtonState::Pressed;
        }
    } else {
        if (currState[static_cast<Uint8>(key)] == 0) {
            return ButtonState::Released;
        } else {
            return ButtonState::Held;
        }
    }
}

bool MouseState::IsButtonPressed(int button) const {
    return (SDL_BUTTON(button) & currButtons) != 0;
}

ButtonState MouseState::GetButtonState(int button) const {
    int mask = SDL_BUTTON(button);
    if ((mask & prevButtons) == 0) {
        if ((mask & currButtons) == 0) {
            return ButtonState::None;
        } else {
            return ButtonState::Pressed;
        }
    } else {
        if ((mask & currButtons) == 0) {
            return ButtonState::Released;
        } else {
            return ButtonState::Held;
        }
    }
}

bool InputSystem::Initialize() {
    state.Keyboard.currState = SDL_GetKeyboardState(NULL);
    memset(state.Keyboard.prevState, 0, SDL_NUM_SCANCODES);

    state.Mouse.currButtons = 0;
    state.Mouse.prevButtons = 0;

    return true;
}

void InputSystem::Shutdown() {
    return;
}

void InputSystem::PrepareForUpdate() {
    memcpy(state.Keyboard.prevState, state.Keyboard.currState, SDL_NUM_SCANCODES);

    state.Mouse.prevButtons = state.Mouse.currButtons;
    state.Mouse.isRelative = false;
    state.Mouse.scrollWheel = Vector2::Zero;
}

void InputSystem::Update() {
    int x = 0, y = 0;
    if (state.Mouse.isRelative) {
        state.Mouse.currButtons = SDL_GetRelativeMouseState(&x, &y);
    } else {
        state.Mouse.currButtons = SDL_GetMouseState(&x, &y);
    }
    
    state.Mouse.mousePosition.x = static_cast<float>(x);
    state.Mouse.mousePosition.y = static_cast<float>(y);
}

void InputSystem::ProcessEvent(SDL_Event& event) {
    switch (event.type) {
    case SDL_MOUSEWHEEL:
        state.Mouse.scrollWheel.x = static_cast<float>(event.wheel.x);
        state.Mouse.scrollWheel.y = static_cast<float>(event.wheel.y);
        break;
    default:
        break;
    }
}

void InputSystem::SetRelativeMouseMode(bool value) {
    SDL_bool relative = value ? SDL_TRUE : SDL_FALSE;
    SDL_SetRelativeMouseMode(relative);
    state.Mouse.isRelative = relative;
}
