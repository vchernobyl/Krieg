#version 330

in vec2 texCoords;
out vec4 color;

uniform sampler2D text;
uniform vec3 uTextColor;

void main() {
    vec4 sampled = vec4(1.0, 1.0, 1.0, texture(text, texCoords).r);
    color = sampled;
}
