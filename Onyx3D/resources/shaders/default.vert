#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;
layout (location = 2) in vec3 normal;
layout (location = 3) in vec2 texcoord;
layout (location = 4) in vec3 tangent;

out VS_OUT{
    vec3 color;
    vec2 texCoord;
    vec3 normal;
    vec3 fragPos;
    mat3 TBN;
    vec3 tangentFragPos;
    vec3 tangentCamPos;
} vs_out;

struct Camera{
    vec3 position;
    vec3 direction;
};
uniform Camera camera;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position = projection * view * model * vec4(position, 1.0);
    vs_out.color = color;
    
    
    vs_out.fragPos = vec3(model * vec4(position, 1.0));
    vs_out.texCoord = vec2(texcoord.x, 1.0 - texcoord.y);
    
    mat3 normalMatrix = transpose(inverse(mat3(model)));
    vec3 T = normalize(normalMatrix * tangent);
    vec3 N = normalize(normalMatrix * normal);
    vec3 B = normalize(cross(T, N));
    vs_out.TBN = transpose(mat3(T, B, N));
    vs_out.normal = N;
    
    
    vs_out.tangentFragPos = vs_out.TBN * vs_out.fragPos;
    vs_out.tangentCamPos = vs_out.TBN * camera.position;
    /*
    vec3 N = normalize(mat3(transpose(inverse(model))) * normal);
    vec3 T = normalize(vec3(model * vec4(tangent, 1.0)));
    //T = normalize(T - dot(T, N) * N);
    
     */
    //vs_out.TBN = mat3(T, B, N);
}
