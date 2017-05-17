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

struct DirectionalLight{
    vec3 direction;
    vec3 color;
    vec3 specular;
    float intensity;
};

struct Lighting{
    vec3 ambient;
 
    int dirlightsnum;
    DirectionalLight directional[1];
};
uniform Lighting lighting_data;


void main()
{
    
    vec4 diffuse = material.color * texture(material.diffuse, fs_in.texCoord);
    outColor = min((0.1f + vec4(lighting_data.ambient,1)) * diffuse, 1);;
}
