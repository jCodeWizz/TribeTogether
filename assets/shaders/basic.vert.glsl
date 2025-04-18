#version 460 core

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inColour;

layout(location = 0) out vec3 outColour;

layout(push_constant) uniform PushConstants {
    mat4 ViewProjection;
    mat4 Transform;
} u_PushConstants;

void main() {
    gl_Position = u_PushConstants.ViewProjection * u_PushConstants.Transform * vec4(inPosition, 1.0);
    outColour = inColour;
}
