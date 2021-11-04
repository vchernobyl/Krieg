#pragma once

class DebugUI {
public:
    DebugUI();
    ~DebugUI();
    void SetFPS(int fps) { this->fps = fps; }
    void Draw(class SpriteBatch& spriteBatch);
private:
    class Font* font;
    class Texture* texture;
    int fps = 0;
};
