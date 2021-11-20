#include "Renderer.h"
#include "SpriteComponent.h"
#include "SpriteBatch.h"
#include "Game.h"
#include "Texture.h"
#include "ParticleComponent.h"
#include "DebugRenderer.h"
#include "DebugUI.h"
#include "Shader.h"
#include "Assert.h"
#include "Camera.h"
#include "Font.h"

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

    debugUI = new DebugUI();

    spriteBatch.Initialize();
    uiSpriteBatch.Initialize();
    DebugRenderer::Initialize();

    font = game->GetFont("data/fonts/Carlito-Regular.ttf");
    uiView = Matrix4::CreateOrtho(screenWidth, screenHeight, 0.0f, 1.0f);

    return true;
}

void Renderer::Shutdown() {
    textureShader->Unload();
    delete textureShader;

    uiShader->Unload();
    delete uiShader;

    delete debugUI;

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

    // TODO: I think it makes total sense to put the sprite-batch specific shader
    // inside the sprite batch itself?
    // Also add a function to set the view projection?
    textureShader->SetActive();
    textureShader->SetMatrixUniform("uViewProjection", view);

    spriteBatch.Begin(SpriteBatch::SortType::FrontToBack);
    for (auto sprite : sprites) {
        if (sprite->IsEnabled()) {
            sprite->Draw(spriteBatch);
        }
    }

    for (auto emitter : particles) {
        emitter->Draw(spriteBatch);
    }
    spriteBatch.End();
    spriteBatch.DrawBatch();

    uiShader->SetActive();
    uiShader->SetMatrixUniform("uViewProjection", view);
 
    uiSpriteBatch.Begin();
    font->RenderText(uiSpriteBatch, "Hello World, pipi gaga!", 1.0f, 0.0f, 1.0f, Color::Blue);
    font->RenderText(uiSpriteBatch, "Hello World, pipi gaga!", 0.0f, 2.0f, 2.0f, Color::Blue);
    uiSpriteBatch.End();
    uiSpriteBatch.DrawBatch();

    DebugRenderer::Draw(view, 1.0f);

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

void Renderer::AddSprite(SpriteComponent* sprite) {
    sprites.push_back(sprite);
}

void Renderer::RemoveSprite(SpriteComponent* sprite) {
    auto iter = std::find(sprites.begin(), sprites.end(), sprite);
    if (iter != sprites.end()) {
        sprites.erase(iter);
    }
}

void Renderer::AddParticles(ParticleComponent* emitter) {
    particles.push_back(emitter);
}

void Renderer::RemoveParticles(ParticleComponent* emitter) {
    auto iter = std::find(particles.begin(), particles.end(), emitter);
    if (iter != particles.end()) {
        particles.erase(iter);
    }
}

bool Renderer::LoadShaders() {
    textureShader = new Shader();
    if (!textureShader->Load("data/shaders/Texture.vert", "data/shaders/Texture.frag")) {
        return false;
    }

    uiShader = new Shader();
    if (!uiShader->Load("data/shaders/Text.vert", "data/shaders/Text.frag")) {
        return false;
    }

    return true;
}
