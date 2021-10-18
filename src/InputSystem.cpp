#include "InputSystem.h"
#include <cstring>

bool KeyboardState::GetKeyValue(SDL_Scancode keyCode) const {
    return currState[keyCode] == 1;
}

ButtonState KeyboardState::GetKeyState(SDL_Scancode keyCode) const {
    if (prevState[keyCode] == 0) {
	if (currState[keyCode] == 0) {
	    return ButtonState::None;
	} else {
	    return ButtonState::Pressed;
	}
    } else {
	if (currState[keyCode] == 0) {
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

void InputSystem::SetRelativeMouseMode(bool value) {
    SDL_bool relative = value ? SDL_TRUE : SDL_FALSE;
    SDL_SetRelativeMouseMode(relative);
    state.Mouse.isRelative = relative;
}
