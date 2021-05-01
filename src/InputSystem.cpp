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

bool InputSystem::Initialize() {
    state.Keyboard.currState = SDL_GetKeyboardState(NULL);
    memset(state.Keyboard.prevState, 0, SDL_NUM_SCANCODES);
    return true;
}

void InputSystem::Shutdown() {
    return;
}

void InputSystem::PrepareForUpdate() {
    memcpy(state.Keyboard.prevState, state.Keyboard.currState, SDL_NUM_SCANCODES);
}

void InputSystem::Update() {
    return;
}
