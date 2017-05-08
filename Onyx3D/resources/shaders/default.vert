#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;
layout (location = 2) in vec3 normal;
layout (location = 3) in vec2 texcoord;
layout (location = 4) in vec3 tangent;

out VS_OUT{
    vec3 color;
    vec2 texCoord;
    vec3 normal;
    vec3 fragPos;
    vec3 tangent;
} vs_out;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position = projection * view * model * vec4(position, 1.0);
    vs_out.color = color;
    vs_out.normal = normalize(mat3(transpose(inverse(model))) * normal);
    //vs_out.normal = normalize(vec3(model * vec4(normal, 1.0)));
    vs_out.tangent = normalize(vec3(model * vec4(tangent, 1.0)));
    vs_out.fragPos = vec3(model * vec4(position, 1.0));
    vs_out.texCoord = vec2(texcoord.x, 1.0 - texcoord.y);
}
