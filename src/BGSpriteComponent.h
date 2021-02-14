#pragma once

#include "SpriteComponent.h"
#include "Actor.h"
#include "Math.h"
#include <vector>

class BGSpriteComponent : public SpriteComponent {
public:
    BGSpriteComponent(class Actor* owner, int drawOrder = 10);
    void Update(float deltaTime) override;
    void Draw(SDL_Renderer* renderer) override;
    void SetBGTextures(const std::vector<SDL_Texture*>& textures);
    void SetScreenSize(const Vector2& size) { screenSize = size; }
    void SetScrollSpeed(float speed) { scrollSpeed = speed; }
    float GetScrollSpeed() const { return scrollSpeed; }
private:
    struct BGTexture {
	SDL_Texture* texture;
	Vector2 offset;
    };
    std::vector<BGTexture> bgTextures;
    Vector2 screenSize;
    float scrollSpeed;
};
