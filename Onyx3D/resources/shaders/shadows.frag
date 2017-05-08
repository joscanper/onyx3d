#version 330 core

#define MAX_EMITTERS 4

in VS_OUT{
    vec3 fragPos;
    vec4 fragPosLightSpace[MAX_EMITTERS];
} fs_in;

out vec4 outColor;


struct ShadowEmitter{
    int number;
    sampler2D shadowMap[MAX_EMITTERS];
    vec3 lightDir[MAX_EMITTERS];
    mat4 lightSpace[MAX_EMITTERS];
};
uniform ShadowEmitter shadowEmitters;


float calculate_shadow(int index, vec4 coord){
    
    vec3 projcoord = coord.xyz / coord.w;
    projcoord = projcoord * 0.5 + 0.5;
    
    if(projcoord.z > 1.0)
        return 1.0f;
    
    
    float closestDepth = texture(shadowEmitters.shadowMap[index], projcoord.xy).r;
    float currentDepth = projcoord.z;
    
    float bias = 0.007f;
    
    float shadow = 0.0;
    
    vec2 texelSize = 1.0 / textureSize(shadowEmitters.shadowMap[index], 0);
    for(int x = -1; x <= 1; ++x)
    {
        for(int y = -1; y <= 1; ++y)
        {
            float pcfDepth = texture(shadowEmitters.shadowMap[index], projcoord.xy + vec2(x, y) * texelSize).r;
            shadow += currentDepth - bias > pcfDepth ? 1.0 : 0.0;
        }    
    }
    
    shadow /= 9.0;
    
    //shadow = currentDepth - bias > closestDepth  ? 1.0 : 0.0;
    return 1-( shadow * 0.5);
}

float calculate_shadows(){
    float shadow = 1;
    for (int i = 0; i < shadowEmitters.number; i++){
        shadow *= calculate_shadow(i, fs_in.fragPosLightSpace[i]);
    }
    
    return shadow;
}

void main()
{
    float shadow = calculate_shadows();
    outColor = vec4(vec3(shadow),1);
}
