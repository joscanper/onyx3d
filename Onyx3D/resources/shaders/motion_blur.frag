//GPU Gems 3
//----------
//https://developer.nvidia.com/gpugems/GPUGems3/gpugems3_pref01.html
//----------

#version 330 core

in vec2 TexCoords;

out vec4 outColor;

uniform mat4 viewProjectionInverseM;
uniform mat4 previousViewProjectionM;

uniform float strength;
uniform float samples;

uniform sampler2D screen;
uniform sampler2D depthTexture;
uniform sampler2D prevDepthTexture;

void main(){
    
    // Get the depth buffer value at this pixel.
    float zOverW = texture(depthTexture, TexCoords).r;
    // H is the viewport position at this pixel in the range -1 to 1.
    vec4 H = vec4(TexCoords.x * 2 - 1, (1 - TexCoords.y) * 2 - 1, zOverW, 1);
    // Transform by the view-projection inverse.
    vec4 D = viewProjectionInverseM * H;
    // Divide by w to get the world position.
    vec4 worldPos = D / D.w;
    
    // Current viewport position
    vec4 currentPos = H;
    // Use the world position, and transform by the previous view-
    // projection matrix.
    vec4 previousPos = previousViewProjectionM* worldPos;
    // Convert to nonhomogeneous points [-1,1] by dividing by w.
    previousPos /= previousPos.w;
    // Use this frame's position and last frame's to compute the pixel
    // velocity.
    vec4 velocity = (previousPos - currentPos) / (2.0f/strength);
    //velocity.y *= 1.0f;
    //   velocity.x *= 0.5f;
    
    // Get the initial color at this pixel.
    vec2 tcoord = TexCoords;
    vec4 screenCol = texture(screen, tcoord);;
    vec4 color = screenCol;
    tcoord += velocity.xy;
    
    velocity *= pow(zOverW,25);
    
    for(int i = 1; i < samples; ++i, tcoord += velocity.xy)
    {
        // Sample the color buffer along the velocity vector.
        vec4 currentColor = texture(screen, tcoord);
        // Add the current color to our color sum.
        color += currentColor;
    }
    
    
    
    // Average all of the samples to get the final blur color.
    //outColor = ;
    
    outColor = color/samples;
    
}
