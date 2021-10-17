#version 330

layout(location = 0) in vec2 vertexPosition;
layout(location = 1) in vec4 vertexColor;

out vec2 fragmentPosition;
out vec4 fragmentColor;

uniform mat4 uViewProjection;

void main() {
     gl_Position = vec4(vertexPosition, 0.0, 1.0) * uViewProjection;

     fragmentPosition = vertexPosition;
     fragmentColor = vertexColor;
}
