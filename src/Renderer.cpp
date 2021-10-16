#include "Renderer.h"
#include "SpriteComponent.h"
#include "Game.h"
#include "Texture.h"
#include "ParticleEmitterComponent.h"
#include "DebugRenderer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Assert.h"

#include <GL/glew.h>
#include <algorithm>
#include <cassert>

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

    CreateSpriteVertices();

    DebugRenderer::Initialize();

    view = Matrix4::CreateScale(32.0f);
    view *= Matrix4::CreateRotationZ(0.0f);
    view *= Matrix4::CreateOrtho(screenWidth, screenHeight, 0.5f, 100.0f);

    return true;
}

void Renderer::Shutdown() {
    delete spriteVertices;

    spriteShader->Unload();
    delete spriteShader;

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
    GL_CALL(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
    GL_CALL(glClear(GL_COLOR_BUFFER_BIT));

    GL_CALL(glEnable(GL_BLEND));
    GL_CALL(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

    spriteShader->SetActive();
    spriteShader->SetMatrixUniform("uViewProjection", view);

    spriteVertices->SetActive();
    for (auto sprite : sprites) {
	sprite->Draw(spriteShader);
    }

    DebugRenderer::End();
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
    int drawOrder = sprite->GetDrawOrder();
    auto iter = sprites.begin();
    while (iter != sprites.end() && drawOrder > (*iter)->GetDrawOrder()) {
	++iter;
    }
    sprites.insert(iter, sprite);
}

void Renderer::RemoveSprite(SpriteComponent* sprite) {
    auto iter = std::find(sprites.begin(), sprites.end(), sprite);
    if (iter != sprites.end()) {
	sprites.erase(iter);
    }
}

void Renderer::AddParticles(ParticleEmitterComponent* emitter) {
    int drawOrder = emitter->GetDrawOrder();
    auto iter = particles.begin();
    while (iter != particles.end() && drawOrder > (*iter)->GetDrawOrder()) {
	++iter;
    }
    particles.insert(iter, emitter);
}

void Renderer::RemoveParticles(ParticleEmitterComponent* emitter) {
    auto iter = std::find(particles.begin(), particles.end(), emitter);
    if (iter != particles.end()) {
	particles.erase(iter);
    }
}

void Renderer::CreateSpriteVertices() {
    // Store vertex data in form (x, y, z, u, v).
    const float vertices[] = {
	-0.5f, 0.5f, 0.0f, 0.0f, 0.0f, // top left
 	0.5f, 0.5f, 0.0f, 1.0f, 0.0f,  // top right
	0.5f, -0.5f, 0.0f, 1.0f, 1.0f, // bottom right
	-0.5f, -0.5f, 0.0, 0.0f, 1.0f  // bottom left
    };

    const unsigned int indices[] = {
	0, 1, 2,
	2, 3, 0
    };

    spriteVertices = new VertexArray(vertices, 4, indices, 6);
}

bool Renderer::LoadShaders() {
    spriteShader = new Shader();
    if (!spriteShader->Load("data/shaders/Sprite.vert", "data/shaders/Sprite.frag")) {
	return false;
    }

    return true;
}
