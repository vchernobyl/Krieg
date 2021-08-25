#version 330

uniform mat4 uWorldTransform;
uniform mat4 uViewProjection;

layout (location = 0) in vec3 inPosition;

void main() {
     gl_Position = vec4(inPosition, 1.0) * uWorldTransform * uViewProjection;
}
