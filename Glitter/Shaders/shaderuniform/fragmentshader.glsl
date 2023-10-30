#version 330 core

out vec4 FragColor;
uniform vec4 outColor; // 这个值由gl cpp设定，在cpp中采用"outColor"访问

void main() {
    FragColor = outColor;
}