#version 330

layout(location = 0) in vec2 vertexPosition;
layout(location = 1) in vec4 vertexColor;
layout(location = 2) in vec2 vertexUV;

out vec2 fragmentPosition;
out vec4 fragmentColor;
out vec2 fragmentUV;

uniform mat4 uViewProjection;

void main() {
    gl_Position = uViewProjection * vec4(vertexPosition, 0.0, 1.0);

    fragmentPosition = vertexPosition;
    fragmentColor = vertexColor;
    fragmentUV = vec2(vertexUV.x, 1.0 - vertexUV.y);
}
