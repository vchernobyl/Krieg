#include "Renderer.h"
#include "SpriteComponent.h"
#include "Game.h"
#include "Texture.h"
#include "ParticleEmitterComponent.h"
#include "DebugRenderer.h"
#include "VertexArray.h"
#include "Shader.h"

#include <glew.h>
#include <SDL_image.h>
#include <algorithm>

Renderer::Renderer(Game* game) : game(game) {}

bool Renderer::Initialize(int windowWidth, int windowHeight) {
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

    window = SDL_CreateWindow("Game", 100, 100, windowWidth, windowHeight, SDL_WINDOW_OPENGL);
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

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer) {
	SDL_Log("Unable to create a renderer: %s", SDL_GetError());
	return false;
    }

    if (IMG_Init(IMG_INIT_PNG) == 0) {
	SDL_Log("Unable to initialize SDL_image: %s", SDL_GetError());
	return false;
    }

    windowSize = Vector2(windowWidth, windowHeight);

    return true;
}

void Renderer::Shutdown() {
    SDL_DestroyRenderer(renderer);
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
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    spriteShader->SetActive();
    spriteVertices->SetActive();

    // TODO: Sprites, particles, tilemap etc. should all be places in a single polymorphic collection.
    // In that case we won't have to create a separate collection for separate drawables. Also they
    // will all be properly sorted between themselves via the `drawOrder` field.
    // An interface with Draw(Renderer*) and GetDrawOrder() should do the job.
    for (auto sprite : sprites) {
	sprite->Draw(spriteShader);
    }

    DebugRenderer::Draw(this);

    SDL_GL_SwapWindow(window);
}

void Renderer::DrawTexture(const Texture* texture, const Rectangle& src, const Rectangle& dst,
			   double angle, SpriteEffect effect) {
    SDL_Rect srcRect;
    srcRect.x = src.position.x;
    srcRect.y = src.position.y;
    srcRect.w = src.size.x;
    srcRect.h = src.size.y;

    SDL_Rect dstRect;
    dstRect.x = (dst.position.x - cameraView.x) * Game::UnitsToPixels;
    dstRect.y = (dst.position.y - cameraView.y) * Game::UnitsToPixels;
    dstRect.w = dst.size.x * Game::UnitsToPixels;
    dstRect.h = dst.size.y * Game::UnitsToPixels;

    SDL_RendererFlip flip = SDL_FLIP_NONE;

    if ((effect & SpriteEffect::FlipHorizontally) != 0)
	flip = static_cast<SDL_RendererFlip>(flip | SDL_FLIP_HORIZONTAL);

    if ((effect & SpriteEffect::FlipVertically) != 0)
	flip = static_cast<SDL_RendererFlip>(flip | SDL_FLIP_VERTICAL);

    SDL_RenderCopyEx(renderer, texture->texture, &srcRect, &dstRect, angle, nullptr, flip);
}

Texture* Renderer::GetTexture(const std::string& fileName) {
    Texture* tex = nullptr;
    auto iter = textures.find(fileName);
    if (iter != textures.end()) {
	tex = iter->second;
    } else {
	tex = new Texture();
	if (tex->Load(fileName, renderer)) {
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
    const float vertices[] = {
	-0.5f, 0.5f, 0.f,
	0.5f, 0.5f, 0.f,
	0.5f, -0.5f, 0.f,
	-0.5f, -0.5f, 0.f
    };

    const unsigned int indices[] = {
	0, 1, 2,
	2, 3, 0
    };

    spriteVertices = new VertexArray(vertices, 4, indices, 6);
}

bool Renderer::LoadShaders() {
    spriteShader = new Shader();
    if (!spriteShader->Load("data/shaders/Basic.vert", "data/shaders/Basic.frag")) {
	return false;
    }

    spriteShader->SetActive();
    return true;
}
