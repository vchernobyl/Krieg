#include "SpriteComponent.h"
#include "Actor.h"
#include "Renderer.h"
#include "Texture.h"
#include "Shader.h"
#include "Assert.h"

SpriteComponent::SpriteComponent(Actor* owner, int drawOrder)
    : Component(owner, drawOrder),
      texture(nullptr),
      drawOrder(drawOrder),
      textureWidth(0),
      textureHeight(0) {
    owner->GetGame()->GetRenderer()->AddSprite(this);
}

SpriteComponent::~SpriteComponent() {
    owner->GetGame()->GetRenderer()->RemoveSprite(this);
}

void SpriteComponent::Draw(Shader* shader) {
    if (texture) {
	float smallest = textureWidth < textureHeight ? textureWidth : textureHeight;
	
	Matrix4 scale = Matrix4::CreateScale(
	    static_cast<float>(textureWidth / smallest),
	    static_cast<float>(textureHeight / smallest),
	    1.0f);
    
	Matrix4 world = scale * owner->GetWorldTransform();
	shader->SetMatrixUniform("uWorldTransform", world);
	texture->SetActive();
    
	GL_CALL(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));
    }
}

void SpriteComponent::SetTexture(Texture* texture) {
    this->texture = texture;
    this->textureWidth = texture->GetWidth();
    this->textureHeight = texture->GetHeight();
}
