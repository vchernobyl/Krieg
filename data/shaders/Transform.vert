#version 330

in vec3 inPosition;

uniform mat4 worldTransform;
uniform mat4 viewProjection;

void main() {
     vec4 pos = vec4(inPosition, 1.0f);
     gl_Position = pos * worldTransform * viewProjection;
}
