#include "Game.h"
#include "Actor.h"
#include "SpriteComponent.h"
#include "Hero.h"
#include "Random.h"
#include "SDL_image.h"
#include <algorithm>

Game::Game() :
    window(nullptr),
    renderer(nullptr),
    isRunning(true),
    updatingActors(false) {}

bool Game::Initialize() {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
	SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
	return false;
    }

    window = SDL_CreateWindow("Game", 100, 100, 1024, 768, 0);
    if (!window) {
	SDL_Log("Unable to create a window: %s", SDL_GetError());
	return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer) {
	SDL_Log("Unable to create a renderer: %s", SDL_GetError());
	return false;
    }

    if (IMG_Init(IMG_INIT_PNG) == 0) {
	SDL_Log("Unable to initialize SDL_image: %s", SDL_GetError());
	return false;
    }

    Random::Init();
    LoadData();
    ticks = SDL_GetTicks();
    return true;
}

void Game::RunLoop() {
    while (isRunning) {
	ProcessInput();
	UpdateGame();
	GenerateOutput();
    }
}

void Game::Shutdown() {
    UnloadData();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
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

void Game::AddSprite(SpriteComponent* sprite) {
    int drawOrder = sprite->GetDrawOrder();
    auto iter = sprites.begin();
    while (iter != sprites.end() && drawOrder > (*iter)->GetDrawOrder()) {
	++iter;
    }
    sprites.insert(iter, sprite);
}

void Game::RemoveSprite(SpriteComponent* sprite) {
    auto iter = std::find(sprites.begin(), sprites.end(), sprite);
    if (iter != sprites.end()) {
	sprites.erase(iter);
    }
}

void Game::AddAsteroid(Asteroid* asteroid) {
    asteroids.emplace_back(asteroid);
}

void Game::RemoveAsteroid(Asteroid* asteroid) {
    auto iter = std::find(asteroids.begin(), asteroids.end(), asteroid);
    if (iter != asteroids.end()) {
	asteroids.erase(iter);
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
	tex = SDL_CreateTextureFromSurface(renderer, surf);
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
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
	switch (event.type) {
	case SDL_QUIT:
	    isRunning = false;
	    break;
	}
    }

    const Uint8* state = SDL_GetKeyboardState(NULL);
    if (state[SDL_SCANCODE_ESCAPE]) {
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
	if (actor->GetState() == Actor::Dead) {
	    deadActors.emplace_back(actor);
	}
    }

    for (auto actor : deadActors) {
	delete actor;
    }
}

void Game::GenerateOutput() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    for (auto sprite : sprites) {
	sprite->Draw(renderer);
    }

    SDL_RenderPresent(renderer);
}

void Game::LoadData() {
    Hero* hero = new Hero(this);
    hero->SetPosition(Vector2(150.0f, 150.0f));
}

void Game::UnloadData() {
    while (!actors.empty()) {
	delete actors.back();
    }

    for (auto tex : textures) {
	SDL_DestroyTexture(tex.second);
    }
    textures.clear();
}