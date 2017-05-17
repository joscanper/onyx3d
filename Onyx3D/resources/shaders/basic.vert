#version 330 core

layout (location = 0) in vec3 position;
layout (location = 3) in vec2 texcoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out VS_OUT{
    vec2 texCoord;
} vs_out;

struct Camera{
    vec4 clippingPlane;
};
uniform Camera camera;


void main()
{
    vec4 worldPos = model * vec4(position, 1.0);
    gl_ClipDistance[0] = dot(worldPos, camera.clippingPlane);
    gl_Position = projection * view * worldPos;
    vs_out.texCoord = texcoord;
}
