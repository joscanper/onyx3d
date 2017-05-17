#version 330 core

in VS_OUT{
    vec2 texCoord;
} fs_in;

out vec4 outColor;

// Material properties ----
struct Material{
    vec4 color;
    sampler2D diffuse;
};
uniform Material material;


void main()
{
    
    outColor = material.color * texture(material.diffuse, fs_in.texCoord);
}
