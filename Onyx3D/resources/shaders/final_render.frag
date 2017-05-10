#version 330 core
in vec2 TexCoords;
out vec4 color;


uniform sampler2D diffuse;
uniform sampler2D shadows;
uniform sampler2D depth;
uniform sampler2D bloom;

// TODO - Make all this Uniforms
float FAR = 1000.0f;
float NEAR = 1.0f;
vec4 FOG_COLOR = vec4(0.5,0.5,0.5,1);
int BLUR_RANGE = 5;

float A = 0.15;
float B = 0.50;
float C = 0.10;
float D = 0.20;
float E = 0.02;
float F = 0.30;
float W = 11.2;

vec4 Uncharted2Tonemap(vec4 x)
{
    return ((x*(A*x+C*B)+D*E)/(x*(A*x+B)+D*F))-E/F;
}

vec4 ToneMapping(vec4 col){
    col *= 16;
    vec4 curr = Uncharted2Tonemap(2.0f*col);
    vec4 whiteScale = 1.0f/Uncharted2Tonemap(vec4(W));
    vec4 color = curr*whiteScale;
    vec3 retColor = pow(color.rgb, vec3(2));
    return vec4(retColor.xyz,1);
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


float linearize_depth(){
    float z = texture(depth, TexCoords).x;
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
    float depth = pow(linearize_depth(),5);
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


void main()
{
    vec4 col = texture(diffuse, TexCoords);
    float shadow = calculate_shadow();
    float fog = calculate_fog();
    vec4 bloomCol = calculate_bloom();
    
    color = ToneMapping(max(clamp(col - col*shadow + FOG_COLOR * fog, 0, 1), bloomCol));
}
