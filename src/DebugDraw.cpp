#include "DebugDraw.h"
#include <SDL.h>

DebugDraw::DebugDraw() {
    // Empty.
}

DebugDraw::~DebugDraw() {
    Shutdown();
}

void DebugDraw::Initialize() {
    shader.Load("data/shaders/Shape.vert", "data/shaders/Shape.frag");

    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ibo);

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(DebugVertex), (void*)offsetof(DebugVertex, position));
    
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(DebugVertex), (void*)offsetof(DebugVertex, color));
    
    glBindVertexArray(0);
}

void DebugDraw::Shutdown() {
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ibo);
}

void DebugDraw::DrawBox(const Vector4& center, const Vector4& color, float angle) {
    // For every call to DrawBox function, reserve space for four debug vertices.
    int i = vertices.size();
    vertices.resize(vertices.size() + 4);

    SDL_Log("size=%d", vertices.size());
    auto halfDims = Vector2(center.z / 2.0f, center.w / 2.0f);

    // Get points centered at the origin.
    auto topLeft = Vector2(-halfDims.x, halfDims.y);
    auto bottomLeft = Vector2(-halfDims.x, -halfDims.y);
    auto bottomRight = Vector2(halfDims.x, - halfDims.y);
    auto topRight = Vector2(halfDims.x, halfDims.y);

    auto positionOffset = Vector2(center.x, center.y);

    // Rotate the points.
    vertices[i].position = Vector2::Rotate(topLeft, angle) + halfDims + positionOffset;
    vertices[i + 1].position = Vector2::Rotate(bottomLeft, angle) + halfDims + positionOffset;
    vertices[i + 2].position = Vector2::Rotate(bottomRight, angle) + halfDims + positionOffset;
    vertices[i + 3].position = Vector2::Rotate(topRight, angle) + halfDims + positionOffset;

    for (int j = i; j < i + 4; j++) {
	vertices[j].color = color;
    }

    indices.reserve(indices.size() + 8);
    indices.push_back(i);
    indices.push_back(i + 1);

    indices.push_back(i + 1);
    indices.push_back(i + 2);

    indices.push_back(i + 2);
    indices.push_back(i + 3);
    
    indices.push_back(i + 3);
    indices.push_back(i);
}

void DebugDraw::DrawCircle(const Vector2& center, const Vector4& color, float radius) { }

void DebugDraw::End() {
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(DebugVertex), nullptr, GL_DYNAMIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(DebugVertex), vertices.data());
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), nullptr, GL_DYNAMIC_DRAW);
    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, indices.size() * sizeof(GLuint), indices.data());
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    numElements = indices.size();
    indices.clear();
    vertices.clear();
}

void DebugDraw::Draw(const Matrix4& projectionMatrix, float lineWidth) {
    shader.SetActive();
    shader.SetMatrixUniform("P", projectionMatrix);

    glLineWidth(lineWidth);
    glBindVertexArray(vao);
    glDrawElements(GL_LINES, numElements, GL_UNSIGNED_INT, 0);
    SDL_Log("elements=%d", numElements);
    glBindVertexArray(0);
}
