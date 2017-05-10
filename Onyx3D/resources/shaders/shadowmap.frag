#version 330 core

#define RENDER_MODE_OPAQUE      0
#define RENDER_MODE_TRANSPARENT 1
#define RENDER_MODE_CUTOUT      2

out vec4 color;

in VS_OUT{
    vec2 texCoord;
} fs_in;

struct Material{
    vec4 color;
    sampler2D diffuse;
    sampler2D specular;
    sampler2D normal;
    float shininess;
    
    samplerCube environment;
    float reflectivity;
    float fresnel;
    int renderMode;
};
uniform Material material;

uniform float near;
uniform float far;

float linearize_depth(float depth)
{
    float z = depth * 2.0 - 1.0; // Back to NDC
    return (2.0 * near * far) / (far + near - z * (far - near));
}

void main()
{
    float depthValue = linearize_depth(gl_FragCoord.z);
    
    if (material.renderMode != RENDER_MODE_OPAQUE && (texture(material.diffuse, fs_in.texCoord).a * material.color.a) < 0.8f)
        discard;
    
    
    color = vec4(vec3(depthValue), 1.0f);
}
