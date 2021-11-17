#version 330

layout(location = 0) in vec4 vertex; // <vec2 pos, vec2 tex>
out vec2 uv;

uniform mat4 uViewProjection;

void main() {
    gl_Position = uViewProjection * vec4(vertex.xy, 0.0, 1.0);
    uv = vec2(vertex.z, 1.0 - vertex.w);
}
