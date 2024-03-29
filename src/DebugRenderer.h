#pragma once

#include "Shader.h"
#include "Maths.h"
#include <vector>
#include <GL/glew.h>

class DebugRenderer {
public:
    DebugRenderer();
    ~DebugRenderer();

    static void Initialize();
    static void Shutdown();

    static void DrawBox(const Vector2& position, const Vector2& size,
                        float angle, const Vector4& color = Color::Green);
    static void DrawBox(const Vector4& dst, float angle, const Vector4& color = Color::Green);
    static void DrawCircle(const Vector2& center, float radius, const Vector4& color = Color::Green);
    static void DrawLine(const Vector2& from, const Vector2& to, const Vector4& color = Color::Green);
    
private:
    friend class Renderer;

    struct DebugVertex {
        Vector2 position;
        Vector4 color;
    };

    static void Draw(const Matrix4& projectionMatrix, float lineWidth);

    static Shader shader;
    static std::vector<DebugVertex> vertices;
    static std::vector<GLuint> indices;
    static GLuint vao, vbo, ibo;
    static int numElements;
};
