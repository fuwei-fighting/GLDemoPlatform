#version 330 core
out vec4 FragColor;

in vec3 outColor;
in vec2 TexCoord;

uniform sampler2D inTexture;
uniform sampler2D outTexture;

void main() {
    FragColor = mix(texture(inTexture, TexCoord) , texture(outTexture, vec2(1 - TexCoord.x, TexCoord.y)), 0.2);
}