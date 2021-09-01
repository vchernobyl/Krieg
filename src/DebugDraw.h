#pragma once

#include "Shader.h"
#include "Math.h"
#include <vector>
#include <glew.h>

class DebugDraw {
public:
    DebugDraw();
    ~DebugDraw();

    void Initialize();
    void Shutdown();
    void DrawBox(const Vector4& dst, const Vector4& color, float angle);
    void DrawCircle(const Vector2& center, const Vector4& color, float radius);
    void End();
    void Draw(const Matrix4& projectionMatrix, float lineWidth);
    
private:
    struct DebugVertex {
	Vector2 position;
	Vector4 color;
    };

    Shader shader;
    std::vector<DebugVertex> vertices;
    std::vector<GLuint> indices;
    GLuint vao = 0, vbo = 0, ibo = 0;
    int numElements = 0;
};
