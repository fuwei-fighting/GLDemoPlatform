#version 330 core

layout (location = 0) in vec3 aPos;

uniform float xDist;

void main() {
    gl_Position = vec4(aPos.x + xDist, aPos.y, aPos.z + xDist, 1.0);
}