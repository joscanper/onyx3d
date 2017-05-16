#version 330 core

#define MAX_DIR_LIGHTS 2
#define MAX_POINT_LIGHTS 8
#define MAX_SPOT_LIGHTS 8

#define RENDER_MODE_OPAQUE      0
#define RENDER_MODE_TRANSPARENT 1
#define RENDER_MODE_CUTOUT      2

in VS_OUT{
    vec3 color;
    vec2 texCoord;
    vec3 normal;
    vec3 fragPos;
    mat3 TBN;
    vec3 tangentFragPos;
    vec3 tangentCamPos;
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
    int renderMode;
    
    float heightScale;
    sampler2D height;
    
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
        vec3 lightdir = fs_in.TBN * normalize(-lighting_data.directional[i].direction);
        diffuse += lighting_data.directional[i].color * abs(max(dot(texnormal,lightdir),0)) * lighting_data.directional[i].intensity;
        
        vec3 halfwaydir = normalize(lightdir + viewdir);
        specular += pow(max(dot(texnormal, halfwaydir),0), material.shininess) * lighting_data.directional[i].specular * texspecular;
    }
    return vec4(diffuse + specular,1);
}

// Point lights
vec4 calculate_point_lights(vec3 texnormal, vec3 texspecular, vec3 viewdir){
    vec3 diffuse = vec3(0,0,0);
    vec3 specular = vec3(0,0,0);
    
    for (int i = 0; i < lighting_data.pointlightsnum; ++i){
        vec3 lightPos = fs_in.TBN * lighting_data.point[i].position;
        vec3 lightfragdir = normalize(lightPos - fs_in.tangentFragPos);
        
        float attenuation = max((1+lighting_data.point[i].range) - distance(lightPos, fs_in.tangentFragPos),0) * lighting_data.point[i].intensity ;
        
        diffuse += lighting_data.point[i].color * attenuation * abs(max(dot(texnormal,lightfragdir),0));
        
        
        vec3 halfwaydir = normalize(lightfragdir + viewdir);
        specular += pow(max(dot(texnormal, halfwaydir),0), material.shininess) * lighting_data.point[i].specular * attenuation * texspecular;
    }
    return vec4(diffuse + specular,1);
}

// Spot lights
vec4 calculate_spot_lights(vec3 texnormal, vec3 texspecular, vec3 viewdir){
    vec3 diffuse = vec3(0,0,0);
    vec3 specular = vec3(0,0,0);
    
    for (int i = 0; i < lighting_data.spotlightsnum; ++i){
        vec3 lightPos = fs_in.TBN * lighting_data.spot[i].position;
        vec3 lightDir = fs_in.TBN * lighting_data.spot[i].direction;
        vec3 lightfragdir = normalize(lightPos - fs_in.tangentFragPos);
        
        float angle = acos(dot(lightfragdir, normalize(lightDir))) * 180.0f / 3.14159265359f;
        
        float dist = abs(distance(lightPos, fs_in.tangentFragPos));
        float attenuation = max((1+lighting_data.spot[i].range) - dist,0) * lighting_data.spot[i].intensity;
        
        float distcenter = (1-min(angle/lighting_data.spot[i].angle,1));
        diffuse += lighting_data.spot[i].color * attenuation * (distcenter + pow(distcenter,8)) * abs(max(dot(texnormal,lightfragdir),0));
        
        vec3 halfwaydir = normalize(lightfragdir + viewdir);
        specular += pow(max(dot(texnormal, halfwaydir),0), material.shininess)* distcenter * (lighting_data.spot[i].intensity/dist) * 0.2 * texspecular * lighting_data.spot[i].specular;
    }
    return vec4(diffuse + specular,1);
}

vec4 calculate_reflection(vec3 texnormal, vec3 texspecular){
    
        vec3 viewdir = normalize(camera.position - fs_in.fragPos);
        vec3 reflectdir = reflect(-viewdir, fs_in.normal);
        
        float rim = 1.0f - pow(max(dot(viewdir, fs_in.normal),0), material.fresnel);
        float reflection = material.reflectivity * texspecular.r * rim;
        reflectdir.x *= -1;
        vec3 refcol = texture(material.environment, reflectdir).rgb;
        return vec4(refcol, length(refcol)) * reflection;
}


vec2 calculate_paralax_mapping(vec2 texCoords, vec3 viewDir)
{
    
    // number of depth layers
    const float minLayers = 15;
    const float maxLayers = 20;
    float numLayers = mix(maxLayers, minLayers, abs(dot(vec3(0.0, 0.0, 1.0), viewDir)));
    //numLayers = 50;
    
    // calculate the size of each layer
    float layerDepth = 1.0 / numLayers;
    // depth of current layer
    float currentLayerDepth = 0.0;
    // the amount to shift the texture coordinates per layer (from vector P)
    vec2 P = viewDir.xy * material.heightScale;
    vec2 deltaTexCoords = P / numLayers;
  
    vec2  currentTexCoords     = texCoords;
    float currentDepthMapValue = texture(material.height, currentTexCoords).r;
    
    while(currentLayerDepth < currentDepthMapValue)
    {
        // shift texture coordinates along direction of P
        currentTexCoords += deltaTexCoords;
        // get depthmap value at current texture coordinates
        currentDepthMapValue = texture(material.height, currentTexCoords).r;
        // get depth of next layer
        currentLayerDepth += layerDepth;
    }
    
   // return currentTexCoords;
    
    // get texture coordinates before collision (reverse operations)
    vec2 prevTexCoords = currentTexCoords - deltaTexCoords;
    
    // get depth after and before collision for linear interpolation
    float afterDepth  = currentDepthMapValue - currentLayerDepth;
    float beforeDepth = texture(material.height, prevTexCoords).r - currentLayerDepth + layerDepth;
    
    // interpolation of texture coordinates
    float weight = afterDepth / (afterDepth - beforeDepth);
    vec2 finalTexCoords = prevTexCoords * weight + currentTexCoords * (1.0 - weight);
    
    return finalTexCoords;
    
}

void main()
{
    vec3 viewdir = normalize(fs_in.tangentCamPos - fs_in.tangentFragPos);
    
    
    vec2 texCoord = material.heightScale > 0 ? calculate_paralax_mapping(fs_in.texCoord, viewdir) : fs_in.texCoord;
    //if(material.heightScale > 0 && (texCoord.x > 1.0 || texCoord.y > 1.0 || texCoord.x < 0.0 || texCoord.y < 0.0))
     //   discard;
    vec3 normal = normalize(texture(material.normal, fs_in.texCoord).xyz * 2.0f - 1.0f);
    
    vec4 diffuse = texture(material.diffuse, texCoord) * material.color;
    
    // TODO - get glossiness and fresnel from specular map
    vec3 specular = texture(material.specular, texCoord).rgb;
    
    vec4 col = vec4(0,0,0,1);
    col = calculate_directional_lights(normal, specular, viewdir);
    col += calculate_point_lights(normal, specular, viewdir);
    col += calculate_spot_lights(normal, specular, viewdir);
    
    
    if (material.reflectivity > 0)
        diffuse += calculate_reflection(normal, specular);
    
    col = min((col + vec4(lighting_data.ambient,1)) * diffuse, 1);
    
    if (material.renderMode == RENDER_MODE_CUTOUT && diffuse.a < 0.8f)
        discard;
    
    outColor = col;
}
