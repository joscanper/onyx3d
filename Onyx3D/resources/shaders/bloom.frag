
#version 330 core

in vec2 TexCoords;

out vec4 outColor;

uniform sampler2D screen;


void main(){
    vec4 col = texture(screen, TexCoords);
    outColor = clamp(col * (length(col) - 0.90f),0,1);
}
