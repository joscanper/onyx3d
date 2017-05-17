#version 330 core

layout (location = 0) in vec3 position;
layout (location = 3) in vec2 texcoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

const float tiling = 1;

out VS_OUT{
    vec4 worldPos;
    vec2 texCoord;
    vec4 fragPos;
} vs_out;

void main()
{
    vs_out.worldPos = model * vec4(position, 1.0);
    vs_out.fragPos = projection * view * vs_out.worldPos;
    gl_Position = vs_out.fragPos;
    vs_out.texCoord = texcoord * tiling;
}
