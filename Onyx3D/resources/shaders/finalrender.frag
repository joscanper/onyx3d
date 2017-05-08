#version 330 core
in vec2 TexCoords;
out vec4 color;


uniform sampler2D diffuse;
uniform sampler2D shadows;
uniform sampler2D depth;

// TODO - Make all this Uniforms
float FAR = 1000.0f;
float NEAR = 1.0f;
vec4 FOG_COLOR = vec4(0.5,0.5,0.5,1);
int BLUR_RANGE = 5;

float SCurve (float x) {
    x = x * 2.0 - 1.0;
    return -x * abs(x) * 0.5 + x + 0.5;
}

vec4 blurH (sampler2D source, vec2 size, vec2 uv, float radius) {
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
        
        for (float x = -BLUR_RANGE; x <= BLUR_RANGE; x++)
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

vec4 blurV (sampler2D source, vec2 size, vec2 uv, float radius) {
    
    if (radius >= 1.0)
    {
        vec4 A = vec4(0.0);
        vec4 C = vec4(0.0);
        
        float height = 1.0 / size.y;
        
        float divisor = 0.0;
        float weight = 0.0;
        
        float radiusMultiplier = 1.0 / radius;
        
        for (float y = -BLUR_RANGE; y <= BLUR_RANGE; y++)
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
    vec4 bH = blurH(shadows, texSize, TexCoords, BLUR_RANGE);
    vec4 bV = blurV(shadows, texSize, TexCoords, BLUR_RANGE);
    
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


void main()
{
    vec4 col = texture(diffuse, TexCoords);
    float shadow = calculate_shadow();
    float fog = calculate_fog();
    
    color = clamp(col - col*shadow + FOG_COLOR * fog, 0, 1);
}
