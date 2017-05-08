#version 330 core

in VS_OUT{
    vec3 texCoord;
} fs_in;

out vec4 outColor;

uniform samplerCube skybox;

void main()
{
    outColor = texture(skybox, fs_in.texCoord);
}
