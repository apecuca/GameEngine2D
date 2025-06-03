#version 330 core

out vec4 FragColor;

in vec2 TexCoord;

uniform vec4 color;

// Sprite animation handling
uniform sampler2D sprite;
uniform ivec2 texSize;

void main()
{
    //FragColor = texture(sprite, TexCoord).rgba * color;
    vec4 texel = texelFetch(sprite, ivec2(TexCoord * vec2(texSize)), 0);
    FragColor = texel * color;
} 