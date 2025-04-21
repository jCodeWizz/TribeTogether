#version 460 core

layout(location = 0) out vec4 outColour;

layout(location = 0) in vec3 inColour;
layout(location = 1) in vec3 inNormal;

void main() {
    outColour = vec4(inColour, 1.0);
}