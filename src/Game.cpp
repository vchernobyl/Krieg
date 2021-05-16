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

    physicsWorld->Update(deltaTime);
    audioSystem->Update(deltaTime);
}

void Game::DrawGame() {
    renderer->Begin();

    tileMapRenderer->Draw(renderer);
    renderer->Draw();
    Debug::Draw(renderer);

    renderer->End();
}

void Game::LoadData() {
    new Player(this);
    new Enemy(this);

    ParticleProps particleProps;
    particleProps.colorBegin = Vector4(254, 212, 123, 255.0f);
    particleProps.colorEnd = Vector4(254, 109, 41, 255.0f / 2);

    particleProps.sizeBegin = 15.0f;
    particleProps.sizeEnd = 0.0f;
    particleProps.sizeVariation = 5.0f;
    particleProps.lifetime = 3.0f;
    particleProps.velocity = Vector2(12.0f, 35.0f);
    particleProps.velocityVariation = Vector2(100.0f, 100.0f);

    auto emitter = new Actor(this);
    emitter->SetPosition(Vector2(300, 700));
    
    auto particles = new ParticleSystem(emitter);
    particles->SetTexture(renderer->GetTexture("assets/Particle.png"));
    particles->SetProps(particleProps);
    particles->SetAmount(3);

    TileMapLoader tileMapLoader(this);
    tileMap = tileMapLoader.Load("assets/prototype_map.tmx");
    tileMapRenderer = new TileMapRenderer(tileMap);

    auto objectGroups = tileMap->GetObjectGroups();
    for (auto objectGroup : objectGroups) {
	for (const auto& object : objectGroup->objects) {
	    auto objectActor = new Actor(this);
	    objectActor->SetPosition(Vector2(object.position.x, object.position.y));

	    auto objectCollider = new BoxColliderComponent(objectActor);
	    objectCollider->SetSize(Vector2(object.size.x, object.size.y));

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
}
