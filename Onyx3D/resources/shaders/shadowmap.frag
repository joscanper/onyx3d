#version 330 core
out vec4 color;
in vec2 TexCoords;


uniform float near;
uniform float far;

float linearize_depth(float depth)
{
    float z = depth * 2.0 - 1.0; // Back to NDC
    return (2.0 * near * far) / (far + near - z * (far - near));
}

void main()
{
    float depthValue = linearize_depth(gl_FragCoord.z);
    color = vec4(vec3(depthValue), 1.0);
}
