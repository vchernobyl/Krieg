#include "DebugUI.h"
#include "Font.h"
#include "Texture.h"
#include "SpriteBatch.h"

DebugUI::DebugUI() {
    font = new Font();
    font->Load("data/fonts/Carlito-Regular.ttf");
}

DebugUI::~DebugUI() {
    delete font;
    delete texture;
}

void DebugUI::Draw(SpriteBatch& spriteBatch) {
}
