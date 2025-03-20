#version 460 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec3 a_Color;
layout(location = 2) in vec3 a_Normal;

layout(location = 0) out vec3 out_color;

layout(push_constant) uniform PushConstants {
	mat4 ViewProjection;
    mat4 Transform;
} u_PushConstants;

void main() {
    gl_Position = u_PushConstants.ViewProjection * u_PushConstants.Transform * vec4(a_Position, 1.0);
    out_color = a_Color;
}