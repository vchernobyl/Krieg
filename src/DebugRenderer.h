#pragma once

#include "Math.h"

#include <vector>
#include <utility>

class Shader;
class VertexArray;
class Shape;

class DebugRenderer {
public:
    static void AddRect(float x, float y, float width, float height, Vector4 color);
    static void AddLine(float x1, float y1, float x2, float y2, Vector4 color);
    static void AddCircle(float centerX, float centerY, float radius, Vector4 color);
private:
    friend class Renderer;

    static bool Initialize();
    static void Draw(Shader* shader);
    static void Shutdown();
    
    static Shader* shapeShader;
    static VertexArray* shapeVAO;
    
    static std::vector<std::pair<Shape*, Vector4>> shapes;
};
