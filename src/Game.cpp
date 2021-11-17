#include "Game.h"
#include "Actor.h"
#include "AudioSystem.h"
#include "InputSystem.h"
#include "PhysicsWorld.h"
#include "Renderer.h"
#include "Random.h"
#include "Math.h"
#include "Font.h"
#include "Camera.h"

#include <algorithm>
#include <memory>

// Game specific, remove later.
#include "SpriteComponent.h"
#include "ParticleComponent.h"
#include "Asteroid.h"
#include "Ship.h"
#include "Enemy.h"
// End

Game::Game() :
    renderer(nullptr),
    inputSystem(nullptr),
    physicsWorld(nullptr),
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

    const auto gravity = Vector2::Zero;
    physicsWorld = new PhysicsWorld(gravity);

    Random::Init();

    mainCamera = new Camera(renderer->GetScreenWidth(), renderer->GetScreenHeight());
    uiCamera = new Camera(renderer->GetScreenWidth(), renderer->GetScreenHeight());

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

    delete mainCamera;
    delete uiCamera;

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

Font* Game::GetFont(const std::string& fileName) {
    auto iter = fonts.find(fileName);
    if (iter != fonts.end()) {
        return iter->second;
    } else {
        Font* font = new Font(this);
        if (font->Load(fileName)) {
            fonts.emplace(fileName, font);
        } else {
            font->Unload();
            delete font;
            font = nullptr;
        }
        return font;
    }
}

Actor* Game::GetActorByTag(const std::string& tag) {
    auto iter = std::find_if(actors.begin(), actors.end(),
                             [&tag](const Actor* actor) { return actor->GetTag() == tag; });
    if (iter != actors.end()) {
        return *iter;
    }
    return nullptr;
}

void Game::ProcessInput() {
    inputSystem->PrepareForUpdate();

    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_QUIT:
            isRunning = false;
            break;
        case SDL_MOUSEWHEEL:
            inputSystem->ProcessEvent(event);
            break;
        default:
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

    static int count = 0;
    if (count++ == 30) {
        SDL_Log("fps: %d", static_cast<int>(1.0f / deltaTime));
        count = 0;
    }

    physicsWorld->Step(0.016f); // Run physics step at 60Hz independent of the frame rate.

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
        if (actor->GetState() == Actor::State::Dead) {
            deadActors.emplace_back(actor);
        }
    }

    for (auto actor : deadActors) {
        delete actor;
    }

    audioSystem->Update(deltaTime);

    mainCamera->Update();
    renderer->SetViewMatrix(mainCamera->GetViewMatrix());

    uiCamera->SetPosition(Vector2(10.5f, -7.5f));
    uiCamera->Update();
    renderer->SetUIViewMatrix(uiCamera->GetViewMatrix());
}

void Game::DrawGame() {
    renderer->Draw();
    font->RenderText("Hello World", 0, 0, 1.0f, Color::White);
}

void Game::LoadData() {
    audioSystem->LoadBank("data/audio/Master.strings.bank");
    audioSystem->LoadBank("data/audio/Master.bank");

    font = GetFont("data/fonts/Carlito-Regular.ttf");
        
    new Ship(this);
    auto e1 = new Enemy(this);
    e1->SetPosition(Vector2(15.0f, -3.5f));
    
    auto e2 = new Enemy(this);
    e2->SetPosition(Vector2(-5.5f, 12.0f));
    
    auto e3 = new Enemy(this);
    e3->SetPosition(Vector2(12.3f, 2.5f));

    const int numAsteroids = 20;
    for (int i = 0; i < numAsteroids; i++) {
        new Asteroid(this);
    }
}

void Game::UnloadData() {
    renderer->UnloadData();
    
    while (!actors.empty()) {
        delete actors.back();
    }
}
