#version 330

in vec2 fragmentUV;
in vec4 fragmentColor;

out vec4 color;

uniform sampler2D text;

void main() {
    vec4 textureColor = vec4(1.0, 1.0, 1.0, texture(text, fragmentUV).r);
    color = fragmentColor * textureColor;
}
