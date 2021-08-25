#include "DebugRenderer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Shapes.h"

#include <glew.h>
#include <cassert>

std::vector<std::pair<Shape*, Vector4>> DebugRenderer::shapes = {};
Shader* DebugRenderer::shapeShader = nullptr;
VertexArray* DebugRenderer::shapeVAO = nullptr;

bool DebugRenderer::Initialize() {
    shapeShader = new Shader();
    if (!shapeShader->Load("data/shaders/Shape.vert", "data/shaders/Shape.frag")) {
	return false;
    }

    const float vertices[] = {
	-0.5f, 0.0f, 0.0f, 0.0f, 0.0f,
	0.5f, 0.0f, 0.0f, 0.0f, 0.0f
    };

    const unsigned int indices[] = { 0, 1 };

    shapeVAO = new VertexArray(vertices, 2, indices, 2);

    return true;
}

void DebugRenderer::Shutdown() {
    delete shapeShader;
    delete shapeVAO;
}

void DebugRenderer::AddRect(float x, float y, float width, float height, Vector4 color) {
}

void DebugRenderer::AddLine(float x1, float y1, float x2, float y2, Vector4 color) {
}

void DebugRenderer::AddCircle(float centerX, float centerY, float radius, Vector4 color) {
}

void DebugRenderer::Draw(Shader* shader) {
    assert(shapeShader);
    assert(shapeVAO);

    shapeShader->SetActive();

    Matrix4 worldTransform = Matrix4::CreateScale(32.0f);
    worldTransform *= Matrix4::CreateRotationZ(0.0f);
    worldTransform *= Matrix4::CreateTranslation(Vector3(0.0f, 0.0f, 0.0f));
    shapeShader->SetMatrixUniform("uWorldTransform", worldTransform);

    Matrix4 projection = Matrix4::CreateSimpleViewProjection(1024, 768);
    shapeShader->SetMatrixUniform("uViewProjection", projection);
	
    shapeVAO->SetActive();
    
    glDrawElements(GL_LINES, 2, GL_UNSIGNED_INT, nullptr);
    
    assert(shapes.empty());
}
