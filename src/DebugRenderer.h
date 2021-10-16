#pragma once

#include "Shader.h"
#include "Math.h"
#include <vector>
#include <GL/glew.h>

class DebugRenderer {
public:
    DebugRenderer();
    ~DebugRenderer();

    static void Initialize();
    static void Shutdown();

    // TODO: Make color optional.
    static void DrawBox(const Vector4& dst, const Vector4& color, float angle);

    // TODO: Make color optional.
    static void DrawCircle(const Vector2& center, const Vector4& color, float radius);

    static void DrawLine(const Vector2& from, const Vector2& to, const Vector4& color);
    
    static void End();
    static void Draw(const Matrix4& projectionMatrix, float lineWidth);
    
private:
    struct DebugVertex {
	Vector2 position;
	Vector4 color;
    };

    static Shader shader;
    static std::vector<DebugVertex> vertices;
    static std::vector<GLuint> indices;
    static GLuint vao, vbo, ibo;
    static int numElements;
};
