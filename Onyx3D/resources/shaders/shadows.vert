#version 330 core
#define MAX_EMITTERS 4

layout (location = 0) in vec3 position;
layout (location = 3) in vec2 texcoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

struct ShadowEmitter{
    int number;
    sampler2D shadowMap[MAX_EMITTERS];
    vec3 lightDir[MAX_EMITTERS];
    mat4 lightSpace[MAX_EMITTERS];
};
uniform ShadowEmitter shadowEmitters;

out VS_OUT{
    vec3 fragPos;
    vec4 fragPosLightSpace[MAX_EMITTERS];
} vs_out;

void main()
{
    gl_Position = projection * view * model * vec4(position, 1.0);
    vs_out.fragPos = vec3(model * vec4(position, 1.0));
    
    for(int i = 0; i < shadowEmitters.number; ++i)
        vs_out.fragPosLightSpace[i] = shadowEmitters.lightSpace[i] * vec4(vs_out.fragPos, 1);
}
