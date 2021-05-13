#include "Game.h"
#include "Actor.h"
#include "InputSystem.h"
#include "AudioSystem.h"
#include "PhysicsWorld.h"
#include "Renderer.h"
#include "BoxColliderComponent.h"
#include "RigidbodyComponent.h"
#include "TileMap.h"
#include "TileMapRenderer.h"
#include "Player.h"
#include "Debug.h"
#include "Enemy.h"
#include "Random.h"
#include "ParticleSystem.h"

#include <SDL_image.h>
#include <algorithm>
#include <memory>

Game::Game() :
    renderer(nullptr),
    inputSystem(nullptr),
    physicsWorld(nullptr),
    tileMapRenderer(nullptr),
    tileMap(nullptr),
    isRunning(true),
    updatingActors(false) {}

bool Game::Initialize() {
    renderer = new Renderer(this);
    if (!renderer->Initialize(1024, 768)) {
	SDL_Log("Failed to initialize the renderer");
	return false;
    }
    
    inputSystem = new InputSystem();
    if (!inputSystem->Initialize()) {
	SDL_Log("Failed to initialize the input system");
	return false;
    }

    audioSystem = new AudioSystem(this);
    if (!audioSystem->Initialize()) {
	SDL_Log("Failed to initializa the audio system");
	return false;
    }

    physicsWorld = new PhysicsWorld();

    Random::Init();

    LoadData();

    ticks = SDL_GetTicks();

    return true;
}

void Game::RunLoop() {
    while (isRunning) {
	ProcessInput();
	UpdateGame();
	DrawGame();
    }
}

void Game::Shutdown() {
    UnloadData();

    renderer->Shutdown();
    delete renderer;

    inputSystem->Shutdown();
    delete inputSystem;

    audioSystem->Shutdown();
    delete audioSystem;

    SDL_Quit();
}

void Game::AddActor(Actor* actor) {
    if (updatingActors) {
	pendingActors.emplace_back(actor);
    } else {
	actors.emplace_back(actor);
    }
}

void Game::RemoveActor(Actor* actor) {
    auto iter = std::find(pendingActors.begin(), pendingActors.end(), actor);
    if (iter != pendingActors.end()) {
	std::iter_swap(iter, pendingActors.end() - 1);
	pendingActors.pop_back();
    }

    iter = std::find(actors.begin(), actors.end(), actor);
    if (iter != actors.end()) {
	std::iter_swap(iter, actors.end() - 1);
	actors.pop_back();
    }
}

SDL_Texture* Game::GetTexture(const std::string& filename) {
    SDL_Texture* tex = nullptr;
    auto iter = textures.find(filename);
    if (iter != textures.end()) {
	tex = iter->second;
    } else {
	SDL_Surface* surf = IMG_Load(filename.c_str());
	if (!surf) {
	    SDL_Log("Failed to load texture file %s", filename.c_str());
	    return nullptr;
	}
	tex = SDL_CreateTextureFromSurface(renderer->GetSDLRenderer(), surf);
	SDL_FreeSurface(surf);
	if (!tex) {
	    SDL_Log("Failed to convert surface to texture for %s", filename.c_str());
	    return nullptr;
	}
	textures.emplace(filename.c_str(), tex);
    }
    return tex;
}

void Game::ProcessInput() {
    inputSystem->PrepareForUpdate();

    SDL_Event event;
    while (SDL_PollEvent(&event)) {
	switch (event.type) {
	case SDL_QUIT:
	    isRunning = false;
	    break;
	}
    }

    inputSystem->Update();
    const InputState& state = inputSystem->GetState();

    if (state.Keyboard.GetKeyState(SDL_SCANCODE_ESCAPE) == ButtonState::Released) {
	isRunning = false;
    }

    updatingActors = true;
    for (auto actor : actors) {
	actor->ProcessInput(state);
    }
    updatingActors = false;
}

void Game::UpdateGame() {
    while (!SDL_TICKS_PASSED(SDL_GetTicks(), ticks + 16));

    float deltaTime = (SDL_GetTicks() - ticks) / 1000.0f;
    if (deltaTime > 0.05f) deltaTime = 0.05f;
    ticks = SDL_GetTicks();

    physicsWorld->Update(deltaTime);

    updatingActors = true;
    for (auto actor : actors) {
	actor->Update(deltaTime);
    }
    updatingActors = false;

    for (auto pending : pendingActors) {
	actors.emplace_back(pending);
    }
    pendingActors.clear();

    std::vector<Actor*> deadActors;
    for (auto actor : actors) {
	if (actor->GetState() == Actor::ActorState::Dead) {
	    deadActors.emplace_back(actor);
	}
    }

    for (auto actor : deadActors) {
	delete actor;
    }

    for (int i = 0; i < 5; i++ ) {
	particleSystem.Emit(particle);
    }

    audioSystem->Update(deltaTime);
    particleSystem.Update(deltaTime);
}

void Game::DrawGame() {
    renderer->Begin();

    tileMapRenderer->Draw(renderer);
    renderer->Draw();
    particleSystem.Draw(renderer);
    Debug::Draw(renderer);

    renderer->End();
}

void Game::LoadData() {
    new Player(this);
    new Enemy(this);

    particle.colorBegin = Vector4(254 / 255.0f, 212 / 255.0f, 123 / 255.0f, 1.0f);
    particle.colorEnd = Vector4(254 / 255.0f, 109 / 255.0f, 41 / 255.0f, 1.0f);

    particle.sizeBegin = 15.0f;
    particle.sizeEnd = 0.0f;
    particle.sizeVariation = 5.0f;
    particle.lifetime = 1.0f;
    particle.velocity = Vector2(12.0f, 35.0f);
    particle.velocityVariation = Vector2(100.0f, 100.0f);
    particle.position = Vector2(400.0f, 400.0f);
    
    particleSystem.SetTexture(renderer->GetTexture("assets/Particle.png"));

    TileMapLoader tileMapLoader(this);
    tileMap = tileMapLoader.Load("assets/prototype_map.tmx");
    tileMapRenderer = new TileMapRenderer(tileMap);

    auto objectGroups = tileMap->GetObjectGroups();
    for (auto objectGroup : objectGroups) {
	for (const auto& object : objectGroup->objects) {
	    auto objectActor = new Actor(this);
	    objectActor->SetPosition(Vector2(object.x, object.y));

	    auto objectCollider = new BoxColliderComponent(objectActor);
	    objectCollider->SetSize(Vector2(object.w, object.h));

	    auto rigidbody = new RigidbodyComponent(objectActor);
	    rigidbody->isKinematic = true;
	}
    }
}

void Game::UnloadData() {
    renderer->UnloadData();
    
    delete tileMapRenderer;
    delete tileMap;

    while (!actors.empty()) {
	delete actors.back();
    }

    for (auto tex : textures) {
	SDL_DestroyTexture(tex.second);
    }
    textures.clear();
}
