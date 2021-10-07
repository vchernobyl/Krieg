#include "DebugDraw.h"
#include "Assert.h"

Shader DebugDraw::shader;
std::vector<DebugDraw::DebugVertex> DebugDraw::vertices = {};
std::vector<GLuint> DebugDraw::indices = {};
GLuint DebugDraw::vao = 0;
GLuint DebugDraw::vbo = 0;
GLuint DebugDraw::ibo = 0;
int DebugDraw::numElements = 0;

DebugDraw::DebugDraw() {
    // Empty.
}

DebugDraw::~DebugDraw() {
    Shutdown();
}

void DebugDraw::Initialize() {
    shader.Load("data/shaders/Shape.vert", "data/shaders/Shape.frag");

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

void DebugDraw::Shutdown() {
    GL_CALL(glDeleteVertexArrays(1, &vao));
    GL_CALL(glDeleteBuffers(1, &vbo));
    GL_CALL(glDeleteBuffers(1, &ibo));
}

void DebugDraw::DrawBox(const Vector4& dst, const Vector4& color, float angle) {
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

void DebugDraw::DrawCircle(const Vector2& center, const Vector4& color, float radius) { }

void DebugDraw::End() {
    GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, vbo));
    GL_CALL(glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(DebugVertex), nullptr, GL_DYNAMIC_DRAW));
    GL_CALL(glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(DebugVertex), vertices.data()));
    GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, 0));

    GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo));
    GL_CALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), nullptr, GL_DYNAMIC_DRAW));
    GL_CALL(glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, indices.size() * sizeof(GLuint), indices.data()));
    GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));

    numElements = indices.size();
    indices.clear();
    vertices.clear();
}

void DebugDraw::Draw(const Matrix4& projectionMatrix, float lineWidth) {
    shader.SetActive();
    shader.SetMatrixUniform("P", projectionMatrix);

    GL_CALL(glLineWidth(lineWidth));
    GL_CALL(glBindVertexArray(vao));
    GL_CALL(glDrawElements(GL_LINES, numElements, GL_UNSIGNED_INT, 0));
    GL_CALL(glBindVertexArray(0));
}
