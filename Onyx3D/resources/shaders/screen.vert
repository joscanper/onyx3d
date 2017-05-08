#version 330 core
layout (location = 0) in vec3 position;
layout (location = 3) in vec2 texCoords;

out vec2 TexCoords;

void main()
{
    gl_Position = vec4(position.x, position.y, position.z, 1.0f);
    TexCoords = texCoords;
}
