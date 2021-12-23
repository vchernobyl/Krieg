#include "Game.h"
#include "Actor.h"
#include "AudioSystem.h"
#include "InputSystem.h"
#include "PhysicsWorld.h"
#include "Renderer.h"
#include "Random.h"
#include "Maths.h"
#include "Font.h"
#include "Camera.h"
#include "UIScreen.h"
#include <algorithm>
#include <memory>

Game::Game() :
    renderer(nullptr),
    inputSystem(nullptr),
    physicsWorld(nullptr),
    isRunning(true),
    updatingActors(false),
    ticks(0),
    deltaTime(0.0f) {}

void Game::Run() {
    if (Initialize()) {
        RunLoop();
    }
    Shutdown();
}

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

    ticks = SDL_GetTicks();

    LoadContent();

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
    UnloadContent();

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

Font* Game::GetFont(const std::string& fileName, int fontSize) {
    auto iter = fonts.find(fileName);
    if (iter != fonts.end()) {
        return iter->second;
    } else {
        Font* font = new Font(this);
        if (font->Load(fileName, fontSize)) {
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

void Game::PushUI(UIScreen* ui) {
    uiStack.emplace_back(ui);
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

    if (state.Keyboard.GetKeyState(Key::Escape) == ButtonState::Released) {
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

    deltaTime = (SDL_GetTicks() - ticks) / 1000.0f;

    // Reduce delta time to a sane default when debugger has paused the game at a breakpoint.
    // TODO: Noincidentally, removing this line improves the performance of the 3rd frame of the game.
    // This needs further investigation.
    if (deltaTime > 0.05f) {
        deltaTime = 0.05f;
    }

    ticks = SDL_GetTicks();

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

    uiCamera->Update();
    renderer->SetUIViewMatrix(uiCamera->GetViewMatrix());

    for (auto ui : uiStack) {
        if (ui->GetState() == UIScreen::State::Active) {
            ui->Update(deltaTime);
        }
    }

    auto iter = uiStack.begin();
    while (iter != uiStack.end()) {
        if ((*iter)->GetState() == UIScreen::State::Closing) {
            delete *iter;
            iter = uiStack.erase(iter);
        } else {
            ++iter;
        }
    }
}

void Game::DrawGame() {
    renderer->Draw();
}

void Game::LoadContent() {
}

void Game::UnloadContent() {
    while (!uiStack.empty()) {
        delete uiStack.back();
        uiStack.pop_back();
    }

    if (renderer) {
        renderer->UnloadContent();
    }
    
    for (auto [_, font] : fonts) {
        font->Unload();
        delete font;
    }

    while (!actors.empty()) {
        delete actors.back();
    }
}
