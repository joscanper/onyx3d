#version 330 core

layout (location = 0) in vec3 position;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out VS_OUT{
    vec4 fragPos;
    vec3 texCoord;
} vs_out;

// -----------------------------
// Camera ----------------------
// -----------------------------
struct Camera{
    vec3 position;
    vec3 direction;
    vec4 clippingPlane;
};
uniform Camera camera;

void main()
{
    vs_out.fragPos = model * vec4(position, 1.0);
    gl_ClipDistance[0] = dot(vs_out.fragPos, camera.clippingPlane);
    gl_Position = projection * mat4(mat3(view)) * vs_out.fragPos;
    vs_out.texCoord = position;
}
