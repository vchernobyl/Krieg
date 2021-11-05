#pragma once

class DebugUI {
public:
    DebugUI();
    ~DebugUI();

    void AddDrawCalls(int drawCalls) { this->drawCalls += drawCalls; }
    void SetFPS(int fps) { this->fps = fps; }

    void Draw(class SpriteBatch& spriteBatch);

private:
    class Font* font;
    class Texture* texture;

    int drawCalls = 0;
    int fps = 0;
};
