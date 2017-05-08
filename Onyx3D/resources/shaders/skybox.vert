#version 330 core

layout (location = 0) in vec3 position;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out VS_OUT{
    vec3 texCoord;
} vs_out;

void main()
{
    gl_Position = projection * mat4(mat3(view)) * model * vec4(position, 1.0);
    vs_out.texCoord = position;
}
