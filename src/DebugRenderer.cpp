#include "DebugRenderer.h"
#include "GLAssert.h"

Shader DebugRenderer::shader;
std::vector<DebugRenderer::DebugVertex> DebugRenderer::vertices = {};
std::vector<GLuint> DebugRenderer::indices = {};
GLuint DebugRenderer::vao = 0;
GLuint DebugRenderer::vbo = 0;
GLuint DebugRenderer::ibo = 0;
int DebugRenderer::numElements = 0;

DebugRenderer::DebugRenderer() {
    // Empty.
}

DebugRenderer::~DebugRenderer() {
    Shutdown();
}

void DebugRenderer::Initialize() {
    shader.Load("data/shaders/Debug.vert", "data/shaders/Debug.frag");

    GL_CALL(glGenVertexArrays(1, &vao));
    GL_CALL(glGenBuffers(1, &vbo));
    GL_CALL(glGenBuffers(1, &ibo));

    GL_CALL(glBindVertexArray(vao));
    GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, vbo));
    GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo));

    GL_CALL(glEnableVertexAttribArray(0));
    GL_CALL(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(DebugVertex), (void*)offsetof(DebugVertex, position)));
    
    GL_CALL(glEnableVertexAttribArray(1));
    GL_CALL(glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(DebugVertex), (void*)offsetof(DebugVertex, color)));
    
    GL_CALL(glBindVertexArray(0));
}

void DebugRenderer::Shutdown() {
    GL_CALL(glDeleteVertexArrays(1, &vao));
    GL_CALL(glDeleteBuffers(1, &vbo));
    GL_CALL(glDeleteBuffers(1, &ibo));
}

void DebugRenderer::DrawBox(const Vector4& dst, float angle, const Vector4& color) {
    // For every call to DrawBox function, reserve space for four debug vertices.
    int i = vertices.size();
    vertices.resize(vertices.size() + 4);

    auto halfDims = Vector2(dst.z / 2.0f, dst.w / 2.0f);

    // Get points centered at the origin.
    auto topLeft = Vector2(-halfDims.x, halfDims.y);
    auto bottomLeft = Vector2(-halfDims.x, -halfDims.y);
    auto bottomRight = Vector2(halfDims.x, - halfDims.y);
    auto topRight = Vector2(halfDims.x, halfDims.y);

    auto positionOffset = Vector2(dst.x, dst.y);

    // Rotate the points.
    vertices[i].position = Vector2::RotatePoint(topLeft, angle) + halfDims + positionOffset;
    vertices[i + 1].position = Vector2::RotatePoint(bottomLeft, angle) + halfDims + positionOffset;
    vertices[i + 2].position = Vector2::RotatePoint(bottomRight, angle) + halfDims + positionOffset;
    vertices[i + 3].position = Vector2::RotatePoint(topRight, angle) + halfDims + positionOffset;

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

void DebugRenderer::DrawCircle(const Vector2& center, float radius, const Vector4& color) {
    const int vertexCount = 100;
    const size_t start = vertices.size();

    // Resize vector for additional vertices for the new circle.
    vertices.resize(start + vertexCount);

    for (int i = 0; i < vertexCount; i++) {
        const float angle = static_cast<float>(i) / vertexCount * 2 * Math::Pi;
        vertices[start + i].position.x = Math::Cos(angle) * radius + center.x;
        vertices[start + i].position.y = Math::Sin(angle) * radius + center.y;
        vertices[start + i].color = color;
    }

    indices.reserve(indices.size() + vertexCount * 2);

    for (int i = 0; i < vertexCount - 1; i++) {
        indices.push_back(start + i);
        indices.push_back(start + i + 1);
    }

    indices.push_back(start + vertexCount - 1);
    indices.push_back(start);
}

void DebugRenderer::DrawLine(const Vector2& from, const Vector2& to, const Vector4& color) {
    const size_t start = vertices.size();

    // Add two vertices for a straight line.
    vertices.resize(start + 2);

    vertices[start].position = from;
    vertices[start].color = color;

    vertices[start + 1].position = to;
    vertices[start + 1].color = color;

    indices.reserve(indices.size() + 2);
    indices.push_back(start);
    indices.push_back(start + 1);
}

void DebugRenderer::Draw(const Matrix4& projectionMatrix, float lineWidth) {
    // Allocate vertex memory and upload the data to the VAO.
    GL_CALL(glBindVertexArray(vao));
    GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, vbo));
    GL_CALL(glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(DebugVertex), nullptr, GL_DYNAMIC_DRAW));
    GL_CALL(glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(DebugVertex), vertices.data()));

    // Allocate index memory and upload the data to the IBO.
    GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo));
    GL_CALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), nullptr, GL_DYNAMIC_DRAW));
    GL_CALL(glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, indices.size() * sizeof(GLuint), indices.data()));

    numElements = indices.size();
    indices.clear();
    vertices.clear();

    shader.SetActive();
    shader.SetMatrixUniform("uViewProjection", projectionMatrix);

    GL_CALL(glLineWidth(lineWidth));
    GL_CALL(glBindVertexArray(vao));
    GL_CALL(glDrawElements(GL_LINES, numElements, GL_UNSIGNED_INT, 0));
    GL_CALL(glBindVertexArray(0));
}
