#include "Renderer.h"
#include "SpriteComponent.h"
#include "SpriteBatch.h"
#include "Game.h"
#include "Texture.h"
#include "ParticleComponent.h"
#include "DebugRenderer.h"
#include "Shader.h"
#include "Assert.h"
#include "Camera.h"
#include "Font.h"
#include "TextComponent.h"
#include "UILayer.h"

#include <GL/glew.h>
#include <algorithm>

Renderer::Renderer(Game* game) : game(game) {}

bool Renderer::Initialize(int screenWidth, int screenHeight) {
    this->screenWidth = screenWidth;
    this->screenHeight = screenHeight;

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        return false;
    }

    // Disable deprecated OpenGL functions.
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    // Set OpenGL version to 3.3.
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

    // Set 8-bits per RGBA channel.
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);

    // Enable double buffer.
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    // Enable hardware acceleration.
    SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);

    window = SDL_CreateWindow("Game", 100, 100, screenWidth, screenHeight, SDL_WINDOW_OPENGL);
    if (!window) {
        SDL_Log("Unable to create a window: %s", SDL_GetError());
        return false;
    }

    context = SDL_GL_CreateContext(window);
    
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        SDL_Log("Failed to initialize GLEW.");
        return false;
    }

    // Clear benign error.
    glGetError();

    if (!LoadShaders()) {
        SDL_Log("Failed to load shaders.");
        return false;
    }

    if (!spriteBatch.Initialize()) {
        SDL_Log("Failed to initialized sprite batch.");
        return false;
    }

    if (!uiSpriteBatch.Initialize()) {
        SDL_Log("Failed to initialized UI batch.");
        return false;
    }

    uiSpriteBatch.SetShader(textShader);

    DebugRenderer::Initialize();

    return true;
}

void Renderer::Shutdown() {
    textShader.Unload();

    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(window);
}

void Renderer::UnloadData() {
    for (auto iter : textures) {
        iter.second->Unload();
        delete iter.second;
    }
    textures.clear();
}

void Renderer::Draw() {
    GL_CALL(glClearColor(0.0, 0.0, 0.0f, 1.0f));
    GL_CALL(glClear(GL_COLOR_BUFFER_BIT));

    GL_CALL(glEnable(GL_BLEND));
    GL_CALL(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

    spriteBatch.SetProjectionMatrix(view);
    spriteBatch.Begin(SpriteBatch::SortType::FrontToBack);
    for (auto drawable : drawables) {
        if (drawable->IsEnabled()) {
            drawable->Draw(spriteBatch);
        }
    }
    spriteBatch.End();
    spriteBatch.DrawBatch();

    uiSpriteBatch.SetProjectionMatrix(uiView);
    uiSpriteBatch.Begin();
    for (auto text : texts) {
        text->Draw(uiSpriteBatch);
    }
    uiSpriteBatch.End();
    uiSpriteBatch.DrawBatch();

    DebugRenderer::Draw(view, 1.0f);

    for (auto ui : game->GetUIStack()) {
        ui->Draw(uiSpriteBatch);
    }

    SDL_GL_SwapWindow(window);
}

Texture* Renderer::GetTexture(const std::string& fileName) {
    Texture* tex = nullptr;
    auto iter = textures.find(fileName);
    if (iter != textures.end()) {
        tex = iter->second;
    } else {
        tex = new Texture();
        if (tex->Load(fileName)) {
            textures.emplace(fileName, tex);
        } else {
            delete tex;
            tex = nullptr;
        }
    }
    return tex;
}

void Renderer::AddDrawable(DrawableComponent* drawable) {
    drawables.push_back(drawable);
}

void Renderer::RemoveDrawable(DrawableComponent* drawable) {
    auto iter = std::find(drawables.begin(), drawables.end(), drawable);
    if (iter != drawables.end()) {
        drawables.erase(iter);
    }
}

void Renderer::AddText(TextComponent* text) {
    texts.push_back(text);
}

void Renderer::RemoveText(TextComponent* text) {
    auto iter = std::find(texts.begin(), texts.end(), text);
    if (iter != texts.end()) {
        texts.erase(iter);
    }
}

bool Renderer::LoadShaders() {
    if (!textShader.Load("data/shaders/Text.vert", "data/shaders/Text.frag")) {
        return false;
    }

    return true;
}
