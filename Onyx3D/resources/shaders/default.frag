#version 330 core

#define MAX_DIR_LIGHTS 2
#define MAX_POINT_LIGHTS 8
#define MAX_SPOT_LIGHTS 8

in VS_OUT{
    vec3 color;
    vec2 texCoord;
    vec3 normal;
    vec3 fragPos;
    vec3 tangent;
} fs_in;

out vec4 outColor;

//#include "shaderlib.glsl"

// -----------------------------
// Material --------------------
// -----------------------------
struct Material{
    vec4 color;
    sampler2D diffuse;
    sampler2D specular;
    sampler2D normal;
    float shininess;
    
    samplerCube environment;
    float reflectivity;
    float fresnel;
};
uniform Material material;



// -----------------------------
// Camera ----------------------
// -----------------------------
struct Camera{
    vec3 position;
    vec3 direction;
};
uniform Camera camera;

// -----------------------------
// Lighting --------------------
// -----------------------------

struct DirectionalLight{
    vec3 direction;
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


// Directional lights
vec4 calculate_directional_lights(vec3 texnormal, vec3 texspecular, vec3 viewdir){
    
    vec3 diffuse = vec3(0,0,0);
    vec3 specular = vec3(0,0,0);

    for (int i = 0; i < lighting_data.dirlightsnum; ++i){
        vec3 lightdir = normalize(-lighting_data.directional[i].direction) ;
        diffuse += lighting_data.directional[i].color * max(dot(texnormal, lightdir), 0) * lighting_data.directional[i].intensity;
        
        vec3 reflectdir = reflect(-lightdir, texnormal);
        specular += pow(max(dot(reflectdir, viewdir),0), material.shininess) * lighting_data.directional[i].specular * texspecular;
    }
    return vec4(diffuse + specular,1);
}

// Point lights
vec4 calculate_point_lights(vec3 texnormal, vec3 texspecular, vec3 viewdir){
    vec3 diffuse = vec3(0,0,0);
    vec3 specular = vec3(0,0,0);
    
    for (int i = 0; i < lighting_data.pointlightsnum; ++i){
        vec3 lightfragdir = normalize(lighting_data.point[i].position - fs_in.fragPos);

        float attenuation = max((1+lighting_data.point[i].range)- distance(lighting_data.point[i].position, fs_in.fragPos),0) * lighting_data.point[i].intensity ;
        
        diffuse += lighting_data.point[i].color * attenuation * abs(max(dot(texnormal,lightfragdir),0));
        
        vec3 reflectdir = reflect(-lightfragdir, texnormal);
        specular += pow(max(dot(reflectdir, viewdir),0), material.shininess) * lighting_data.point[i].specular * attenuation * texspecular;
    }
    return vec4(diffuse + specular,1);
}

// Spot lights
vec4 calculate_spot_lights(vec3 texnormal, vec3 texspecular, vec3 viewdir){
    vec3 diffuse = vec3(0,0,0);
    vec3 specular = vec3(0,0,0);
    
    for (int i = 0; i < lighting_data.spotlightsnum; ++i){
        vec3 lightfragdir = normalize(lighting_data.spot[i].position - fs_in.fragPos);
        float angle = acos(dot(lightfragdir, normalize(lighting_data.spot[i].direction))) * 180.0f / 3.14159265359f;
        
        float dist = abs(distance(lighting_data.spot[i].position, fs_in.fragPos));
        float attenuation = max((1+lighting_data.spot[i].range) - dist,0) * lighting_data.spot[i].intensity;
        
        float distcenter = (1-min(angle/lighting_data.spot[i].angle,1));
        diffuse += lighting_data.spot[i].color * attenuation * (distcenter + pow(distcenter,8)) * abs(max(dot(texnormal,lightfragdir),0));
        
        vec3 reflectdir = reflect(-lightfragdir, texnormal);
        
        specular += pow(max(dot(reflectdir, viewdir),0), material.shininess)* distcenter * (lighting_data.spot[i].intensity/dist) * 0.2 * texspecular * lighting_data.spot[i].specular;
    }
    return vec4(diffuse + specular,1);
}

vec4 calculate_reflection(vec3 texnormal, vec3 texspecular, vec3 viewdir){
    
        vec3 reflectdir = reflect(-viewdir, texnormal);
        
        float rim = 1.0f - pow(max(dot(viewdir, texnormal),0), material.fresnel);
        float reflection = material.reflectivity * texspecular.r * rim;
        reflectdir.x *= -1;
        vec3 refcol = texture(material.environment, reflectdir).rgb;
        return vec4(refcol, length(refcol)) * reflection;

}

vec3 calculate_bumped_normal()
{
    vec3 Normal = fs_in.normal;
    vec3 Tangent = fs_in.tangent;
    Tangent = normalize(Tangent - dot(Tangent, Normal) * Normal);
    vec3 Bitangent = cross(Tangent, Normal);
    vec3 BumpMapNormal = texture(material.normal, fs_in.texCoord).xyz;
    BumpMapNormal = 2.0 * BumpMapNormal - vec3(1.0, 1.0, 1.0);
    vec3 NewNormal;
    mat3 TBN = mat3(Tangent, Bitangent, Normal);
    NewNormal = TBN * BumpMapNormal;
    NewNormal = normalize(NewNormal);
    return NewNormal;
}

void main()
{
    vec3 viewdir = normalize(camera.position - fs_in.fragPos);
    vec3 normal = calculate_bumped_normal();
    vec4 diffuse = texture(material.diffuse, fs_in.texCoord) * material.color;
    
    // TODO - get glossiness and fresnel from specular map
    vec3 specular = texture(material.specular, fs_in.texCoord).rgb;
    
    vec4 col = vec4(0,0,0,1);
    col = calculate_directional_lights(normal, specular, viewdir);
    col += calculate_point_lights(normal, specular, viewdir);
    col += calculate_spot_lights(normal, specular, viewdir);
    
    
    if (material.reflectivity > 0)
        diffuse += calculate_reflection(normal, specular, viewdir);
    
    outColor = min((col + vec4(lighting_data.ambient,1)) * diffuse, 1);
    
    
}
