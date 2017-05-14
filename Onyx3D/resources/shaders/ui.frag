#version 330 core
in vec2 TexCoords;
out vec4 outColor;

uniform sampler2D tex;
uniform vec4 color;

void main()
{
    vec4 sampled = vec4(1.0, 1.0, 1.0, texture(tex, TexCoords).r);
    outColor = color * sampled;
}
