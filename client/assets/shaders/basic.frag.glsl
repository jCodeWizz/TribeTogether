#version 460 core

layout(location = 0) out vec4 outColour;

layout(location = 0) in vec3 inColour;
layout(location = 1) in vec3 inNormal;

void main() {
    vec3 lightDir = normalize(vec3(0.3, 0.7, 0.3));

    float intensity = max(0.15, dot(inNormal, lightDir));

    outColour = vec4(vec3(intensity) * inColour, 1.0);
}