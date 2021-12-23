#pragma once

#include "Maths.h"
#include <SDL/SDL.h>
#include <cstdint>

enum class Key {
    Unknown = 0,

    A = 4,
    B = 5,
    C = 6,
    D = 7,
    E = 8,
    F = 9,
    G = 10,
    H = 11,
    I = 12,
    J = 13,
    K = 14,
    L = 15,
    M = 16,
    N = 17,
    O = 18,
    P = 19,
    Q = 20,
    R = 21,
    S = 22,
    T = 23,
    U = 24,
    V = 25,
    W = 26,
    X = 27,
    Y = 28,
    Z = 29,

    Num1 = 30,
    Num2 = 31,
    Num3 = 32,
    Num4 = 33,
    Num5 = 34,
    Num6 = 35,
    Num7 = 36,
    Num8 = 37,
    Num9 = 38,
    Num0 = 39,

    Return = 40,
    Escape = 41,
    Backspace = 42,
    Tab = 43,
    Space = 44,

    Minus = 45,
    Equals = 46,
    Leftbracket = 47,
    Rightbracket = 48,
    Backslash = 49,
    Nonushash = 50,
    Semicolon = 51,
    Apostrophe = 52,
    Grave = 53,
    Comma = 54,
    Period = 55,
    Slash = 56,

    Capslock = 57,

    F1 = 58,
    F2 = 59,
    F3 = 60,
    F4 = 61,
    F5 = 62,
    F6 = 63,
    F7 = 64,
    F8 = 65,
    F9 = 66,
    F10 = 67,
    F11 = 68,
    F12 = 69,

    Pause = 72,
    Insert = 73,
    Home = 74,
    Pageup = 75,
    Delete = 76,
    End = 77,
    Pagedown = 78,
    Right = 79,
    Left = 80,
    Down = 81,
    Up = 82,

    Lctrl = 224,
    Lshift = 225,
    Lalt = 226,
    Rctrl = 228,
    Rshift = 229,
    Ralt = 230,
};

enum class ButtonState {
    None,
    Pressed,
    Released,
    Held
};

class KeyboardState {
public:
    friend class InputSystem;

    bool IsKeyPressed(Key key) const;
    ButtonState GetKeyState(Key key) const;
private:
    const Uint8* currState;
    Uint8 prevState[SDL_NUM_SCANCODES];
};

class MouseState {
public:
    friend class InputSystem;

    const Vector2& GetPosition() const { return mousePosition; }
    const Vector2& GetScrollWheel() const { return scrollWheel; }
    bool IsRelative() const { return isRelative; }

    bool IsButtonPressed(int button) const;
    ButtonState GetButtonState(int button) const;
private:
    Vector2 mousePosition;
    Uint32 currButtons;
    Uint32 prevButtons;
    bool isRelative;
    Vector2 scrollWheel;
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

    void ProcessEvent(SDL_Event& event);

    const InputState& GetState() const { return state; }
    void SetRelativeMouseMode(bool value);
private:
    InputState state;
};
