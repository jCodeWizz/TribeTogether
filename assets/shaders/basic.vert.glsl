#version 460 core

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inColour;

layout(location = 0) out vec3 outColour;

void main() {
    gl_Position = vec4(inPosition, 1.0);
    outColour = inColour;
}
