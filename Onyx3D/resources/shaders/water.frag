#version 330 core

#define MAX_DIR_LIGHTS 2
#define MAX_POINT_LIGHTS 8
#define MAX_SPOT_LIGHTS 8

#define NEAR 0.1f
#define FAR 1000.0f

in VS_OUT{
    vec4 worldPos;
    vec2 texCoord;
    vec4 fragPos;
    
    
} fs_in;

out vec4 outColor;


struct Camera{
    vec3 position;
};
uniform Camera camera;

struct Water{
    sampler2D reflection;
    sampler2D refraction;
    sampler2D refractionDepth;
    float waveStrength;
    float speed;
    vec3 color;
    float density;
    float specular;
    float tiling;
};
uniform Water water;

struct Material{
    sampler2D dudv;
    sampler2D normal;
};
uniform Material material;


// -----------------------------
// Lighting --------------------
// -----------------------------

struct DirectionalLight{
    vec3 direction;
    vec3 position;
    vec3 color;
    vec3 specular;
    float intensity;
};
struct PointLight{
    float range;
    vec3 position;
    vec3 color;
    vec3 specular;
    float intensity;
};

struct SpotLight{
    float range;
    vec3 position;
    vec3 direction;
    vec3 color;
    float angle;
    vec3 specular;
    float intensity;
};

struct Lighting{
    vec3 ambient;
    
    int pointlightsnum;
    PointLight point[MAX_POINT_LIGHTS];
    
    int dirlightsnum;
    DirectionalLight directional[MAX_DIR_LIGHTS];
    
    int spotlightsnum;
    SpotLight spot[MAX_SPOT_LIGHTS];
};
uniform Lighting lighting_data;



uniform float time;


vec3 calculate_dir_lighting(vec3 normal, vec3 viewDir){
    vec3 specular = vec3(0,0,0);
    for (int i = 0; i < lighting_data.dirlightsnum; ++i){
        DirectionalLight l = lighting_data.directional[i];
        vec3 dirFromLight = normalize(fs_in.worldPos.xyz - l.position);
        vec3 reflectdir = reflect(dirFromLight, normal);
        
        specular += l.color * pow(max(dot(reflectdir, viewDir), 0.0f), water.specular);
    }
    return specular;
}

vec3 calculate_spot_lighting(vec3 normal, vec3 viewDir){
    vec3 specular = vec3(0,0,0);
    for (int i = 0; i < lighting_data.dirlightsnum; ++i){
        SpotLight l = lighting_data.spot[i];
        vec3 dirFromLight = normalize(fs_in.worldPos.xyz - l.position);
        vec3 reflectdir = reflect(dirFromLight, normal);
        
        specular += l.color * pow(max(dot(reflectdir, viewDir), 0.0f), water.specular);
    }
    return specular;
}

float linearize_depth(float z){
    return (2.0f * NEAR) / (FAR + NEAR - z * (FAR - NEAR));
}

void main()
{
    
    vec2 waterCoord = (fs_in.fragPos.xy / fs_in.fragPos.w) / 2.0f + 0.5f;
    
    vec2 refractionCoord = waterCoord;
    vec2 reflectionCoord = waterCoord;
    reflectionCoord.y = 1 - reflectionCoord.y;
    
    
    float floorDist = linearize_depth(texture(water.refractionDepth, refractionCoord).r);
    float waterDist = linearize_depth(gl_FragCoord.z);
    float waterDepth = clamp((floorDist - waterDist) * 100.0f, 0, 1) ;
    
    
    vec2 dist1 = texture(material.dudv, vec2(fs_in.texCoord.x + time * water.speed, fs_in.texCoord.y)).rg * 2.0f - 1.0f;
    vec2 dist2 = texture(material.dudv, vec2(fs_in.texCoord.x - time * water.speed, fs_in.texCoord.y)).rg * 2.0f - 1.0f;
    
    vec2 distCoord = (dist1+dist2) * water.waveStrength * waterDepth;// * (1.0f-waterDist);
    
    refractionCoord += distCoord;
    reflectionCoord += distCoord;
    
    vec3 normal = texture(material.normal, distCoord).rgb;
    normal = vec3(normal.r* 2.0f - 1.0f, normal.b, normal.g* 2.0f - 1.0f);
    normal = normalize(normal);
    
    vec3 dirToCam = normalize(camera.position - fs_in.worldPos.xyz);
    float fresnel = dot(normal, dirToCam);
    fresnel = pow(fresnel, 0.2f);
    vec3 refraction = texture(water.refraction, refractionCoord).rgb;
    vec3 reflection = texture(water.reflection, reflectionCoord).rgb;
    
    vec3 light = calculate_dir_lighting(normal, dirToCam);
    //light *= calculate_spot_lighting(normal, dirToCam);
    
    //float waterDensity = waterDepth;// * 0.1f;
    //refraction += waterColor;
    vec3 ref = mix(reflection, refraction, clamp(fresnel-water.density,0,1));
    ref = mix(ref, ref * water.color, clamp(waterDepth * water.density,0,1));//clamp(1.0f-waterDepth,0,1);
    
    outColor = vec4(ref + light, 1);
}
