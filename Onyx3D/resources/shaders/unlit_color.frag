#version 330 core

out vec4 outColor;

// Material properties ----
struct Material{
    vec4 color;
};
uniform Material material;

void main()
{
    outColor = material.color;
}
