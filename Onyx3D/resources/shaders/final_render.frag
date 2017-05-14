#version 330 core
in vec2 TexCoords;
out vec4 outColor;


uniform sampler2D diffuse;
uniform sampler2D shadows;
uniform sampler2D depth;
uniform sampler2D bloom;

// TODO - Make all this Uniforms
float FAR = 1000.0f;
float NEAR = 1.0f;
vec4 FOG_COLOR = vec4(0.5,0.5,0.5,1);
int BLUR_RANGE = 5;

vec4 ToneMapping(vec4 col){
    vec3 x = max(vec3(0),col.rgb-0.004); // Filmic Curve
    vec3 retColor = (x*(6.2*x+.5))/(x*(6.2*x+1.7)+0.06);
    return vec4(retColor,1);
}

float rand(vec2 co){
    return fract(sin(dot(co.xy ,vec2(12.9898,78.233))) * 43758.5453);
}

float SCurve (float x) {
    x = x * 2.0 - 1.0;
    return -x * abs(x) * 0.5 + x + 0.5;
}

vec4 blurH (sampler2D source, vec2 size, vec2 uv, float radius, float blur_size) {
    if (radius >= 1.0)
    {
        vec4 A = vec4(0.0);
        vec4 C = vec4(0.0);
        
        float width = 1.0 / size.x;
        
        float divisor = 0.0;
        float weight = 0.0;
        
        float radiusMultiplier = 1.0 / radius;
        
        // Hardcoded for radius 20 (normally we input the radius
        // in there), needs to be literal here
        
        for (float x = -blur_size; x <= blur_size; x++)
        {
            A = texture(source, uv + vec2(x * width, 0.0));
            
            weight = SCurve(1.0 - (abs(x) * radiusMultiplier));
            
            C += A * weight;
            
            divisor += weight;
        }
        
        return vec4(C.r / divisor, C.g / divisor, C.b / divisor, 1.0);
    }
    
    return texture(source, uv);
}

vec4 blurV (sampler2D source, vec2 size, vec2 uv, float radius, float blur_size ) {
    
    if (radius >= 1.0)
    {
        vec4 A = vec4(0.0);
        vec4 C = vec4(0.0);
        
        float height = 1.0 / size.y;
        
        float divisor = 0.0;
        float weight = 0.0;
        
        float radiusMultiplier = 1.0 / radius;
        
        for (float y = -blur_size; y <= blur_size; y++)
        {
            A = texture(source, uv + vec2(0.0, y * height));
            
            weight = SCurve(1.0 - (abs(y) * radiusMultiplier));
            
            C += A * weight;
            
            divisor += weight;
        }
        
        return vec4(C.r / divisor, C.g / divisor, C.b / divisor, 1.0);
    }
    
    return texture(source, uv);
}


float linearize_depth(vec2 coord){
    float z = texture(depth, coord).x;
    return (2.0 * NEAR) / (FAR + NEAR - z * (FAR - NEAR));
}

float calculate_shadow(){
    vec2 texSize = textureSize(shadows,0);
    vec4 bH = blurH(shadows, texSize, TexCoords, 3, BLUR_RANGE);
    vec4 bV = blurV(shadows, texSize, TexCoords, 3, BLUR_RANGE);
    
    vec4 shadow = (bH + bV) / 2.0f;
    //float depth = pow(linearize_depth(),4);
    return (1 - shadow.r) ;// * (1.0f-depth);
}

float calculate_fog(){
    float depth = pow(linearize_depth(TexCoords),5);
    if (depth == 1)
        return 0;
    return depth;
}

vec4 calculate_bloom(){
    vec2 texSize = textureSize(shadows,0);
    vec4 bH = blurH(bloom, texSize, TexCoords, 2,3);
    vec4 bV = blurV(bloom, texSize, TexCoords, 2,3);
    return (bH + bV) / 2.0f;
}

vec3 ssao_samples[16] = vec3[](
    vec3( 0.5381, 0.1856,-0.4319), vec3( 0.1379, 0.2486, 0.4430),
    vec3( 0.3371, 0.5679,-0.0057), vec3(-0.6999,-0.0451,-0.0019),
    vec3( 0.0689,-0.1598,-0.8547), vec3( 0.0560, 0.0069,-0.1843),
    vec3(-0.0146, 0.1402, 0.0762), vec3( 0.0100,-0.1924,-0.0344),
    vec3(-0.3577,-0.5301,-0.4358), vec3(-0.3169, 0.1063, 0.0158),
    vec3( 0.0103,-0.5869, 0.0046), vec3(-0.0897,-0.4940, 0.3287),
    vec3( 0.7119,-0.0154,-0.0918), vec3(-0.0533, 0.0596,-0.5411),
    vec3( 0.0352,-0.0631, 0.5460), vec3(-0.4776, 0.2847,-0.0271)
);


float calculate_ssao(){
    float falloff = 0.05;
    float area = 0.005;
    int num_samples = 16;
    
    float fragDepth = linearize_depth(TexCoords);
    vec3 fragPos = vec3(TexCoords,fragDepth);
    
    float occlusion = 0;
    float radius = 0.003 / fragDepth;
    
    for (int i = 0; i < num_samples; i++){
        vec3 pos = fragPos + radius * ssao_samples[i];
        float occ_depth = linearize_depth(clamp(pos.xy,0,1));
        float diff = fragDepth - occ_depth;
        
        if (diff < radius)
            occlusion += (1-smoothstep(falloff, area, clamp(diff/radius,0,1)));
    }
    
    
    return  clamp(1.0 - occlusion / num_samples,0,1);
}

void main()
{
    vec4 col = texture(diffuse, TexCoords);
    float shadow = calculate_shadow();
    float fog = calculate_fog();
    vec4 bloomCol = calculate_bloom();
    float ssao = 1;//calculate_ssao();
    
    outColor = ToneMapping(max(clamp(col - col*shadow, 0, 1), bloomCol) * ssao);
}
