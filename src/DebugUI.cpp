#include "DebugUI.h"
#include "Font.h"
#include "Texture.h"
#include "SpriteBatch.h"

DebugUI::DebugUI() {
    font = new Font();
    font->Load("data/fonts/Carlito-Regular.ttf");
    texture = font->RenderText("FPS: 0");
}

DebugUI::~DebugUI() {
    delete font;
    delete texture;
}

void DebugUI::Draw(SpriteBatch& spriteBatch) {
    // TODO: Conversion to unit size has to be done elsewhere, ideally in a centralized manner.
    auto dest = Vector4(0.0f, 0.0f, texture->GetWidth() / 64.0f, texture->GetHeight() / 64.0f);
    spriteBatch.Draw(dest, Vector4(0.0f, 0.0f, 1.0f, 1.0f), texture->GetID(), 0, Color::White);

    // TODO: Should be like this in the end:
    // font->Draw(spriteBatch, "text");
}
