#include "Game.h"
#include "Actor.h"
#include "InputSystem.h"
#include "AudioSystem.h"
#include "PhysicsWorld.h"
#include "Renderer.h"
#include "BoxColliderComponent.h"
#include "RigidbodyComponent.h"
#include "ParticleEmitterComponent.h"
#include "TileMap.h"
#include "TileMapRenderer.h"
#include "Player.h"
#include "Enemy.h"
#include "Random.h"
#include "Math.h"

#include <algorithm>
#include <memory>

Game::Game() :
    renderer(nullptr),
    inputSystem(nullptr),
    physicsWorld(nullptr),
    tileMapRenderer(nullptr),
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

    const auto gravity = Vector2(0.0f, 30.0f);
    physicsWorld = new PhysicsWorld(gravity);

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

    physicsWorld->Shutdown();
    delete physicsWorld;

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

    physicsWorld->Step(0.016f); // Run physics step at 60Hz independent of the frame rate.
    audioSystem->Update(deltaTime);
}

void Game::DrawGame() {
    renderer->Begin();

    tileMapRenderer->Draw(renderer);
    renderer->Draw();

    renderer->End();
}

void Game::LoadData() {
    new Player(this);
    new Enemy(this);

    auto tileMap = TileMap(this, "assets/prototype_map.tmx");
    tileMapRenderer = new TileMapRenderer(tileMap);

    auto objectGroups = tileMap.GetObjectGroups();
    for (auto objectGroup : objectGroups) {
	for (const auto& object : objectGroup.objects) {
	    auto objectActor = new Actor(this);
	    objectActor->SetPosition(Vector2(object.position.x, object.position.y));

	    new RigidbodyComponent(objectActor, MotionType::Static);
	    auto box = new BoxColliderComponent(objectActor, object.size);
	    box->SetCollisionFilter(CollisionCategory::Ground, CollisionCategory::Default);
	}
    }
}

void Game::UnloadData() {
    renderer->UnloadData();
    
    delete tileMapRenderer;

    while (!actors.empty()) {
	delete actors.back();
    }
}
