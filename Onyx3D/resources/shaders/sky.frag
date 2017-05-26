#version 330 core

out vec4 outColor;

in VS_OUT{
    vec4 fragPos;
    vec3 texCoord;
} fs_in;

// Material properties ----
struct Material{
    vec4 color;
};
uniform Material material;

// -----------------------------
// Camera ----------------------
// -----------------------------
struct Camera{
    vec3 position;
    vec3 direction;
    vec4 clippingPlane;
};
uniform Camera camera;

uniform vec3 sunDir;

//const float dayTime = 0.1f; // TODO - Calculate this based on the sun position;

const vec3 dayGrad[3] = vec3[3](
                                vec3(0.81,0.86,0.96),
                                vec3(0.35,0.46,0.74),
                                vec3(0.07,0.25,0.88)
                                );


const vec3 sunsetGrad[3] = vec3[3](
                                vec3(0.97,0.28,0.05),
                                //vec3(0.74,0.43,0.04),
                                vec3(0.15,0.15,0.38),
                                vec3(0.15,0.15,0.38)
                                );

const vec3 nightGrad[3] = vec3[3](
                                vec3(0.76,0.78,0.60),
                                vec3(0.10,0.42,0.69),
                                vec3(0.00,0.06,0.13)
                                );

void main()
{
    
    
    //dayTime = 0;
    
    vec3 col;
    
    float dayY = pow(fs_in.texCoord.y * 3,0.45);
    vec3 daycol1 = mix(dayGrad[0], dayGrad[1], clamp(dayY,0,1));
    vec3 daycol2 = mix(dayGrad[1], dayGrad[2], clamp(dayY-1,0,1));
    vec3 daycol = mix(daycol1, daycol2, clamp(dayY-1,0,1));
    
    float sunsetY = pow(fs_in.texCoord.y * 1,0.8);
    vec3 sunsetcol1 = mix(sunsetGrad[0], sunsetGrad[1], clamp(sunsetY,0,1)) * 0.8;
    vec3 sunsetcol2 = mix(sunsetGrad[1], sunsetGrad[2], clamp(sunsetY-1,0,1)) * 0.2;
    vec3 sunsetcol = mix(sunsetcol1, sunsetcol2, clamp(sunsetY-1,0,1));
    
    float nightY = pow(fs_in.texCoord.y * 3,0.45);
    vec3 nightcol1 = mix(nightGrad[0], nightGrad[1], clamp(nightY,0,1)) * 0.1;
    vec3 nightcol2 = mix(nightGrad[1], nightGrad[2], clamp(nightY-1,0,1)) * 0.1;
    vec3 nightcol = mix(nightcol1, nightcol2, clamp(nightY-1,0,1));
    
    vec3 dirToSun = normalize(sunDir);
    vec3 dirToFrag = normalize(vec3(fs_in.texCoord));
    float FdotS = max(dot(dirToSun, dirToFrag),0);
    float dayTime = dot(vec3(0,1,0), dirToSun);
    
    float sunHeight = clamp(1-dot(dirToSun, vec3(0,1,0)),0,1);
    float fragHeight = clamp(1-dot(dirToFrag, vec3(0,1,0)),0,1);
    float UPdotS = pow(fragHeight * sunHeight,30);
    
    float fixedDayTime = pow(dayTime,0.8);
    if (dayTime > 0)
        col = mix(sunsetcol, daycol, fixedDayTime);
    else
        col = mix(sunsetcol, nightcol, fixedDayTime);
    
    col = mix(col, pow(col,vec3(0.7)), max(FdotS,0));
    col = mix(col, col+FdotS/1.5, pow(FdotS,350) + UPdotS * pow(FdotS,10));
    
    //col = vec3(UPdotS,0,0);
    if (FdotS > 0.9995)
        col = vec3(1,1,1);
    
    outColor = vec4(col,1);//vec4(0,0,1,1);
}