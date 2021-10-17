#version 330

in vec2 fragmentPosition;
in vec4 fragmentColor;
in vec2 fragmentUV;

out vec4 color;

uniform sampler2D uTexture;

void main() {
    vec4 textureColor = texture(uTexture, fragmentUV);
    color = fragmentColor * textureColor;
}
