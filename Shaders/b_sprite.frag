#version 330 core

out vec4 FragColor;

in vec2 TexCoord;

uniform vec4 color;

// Sprite animation handling
uniform bool hasSprite;
uniform sampler2D sprite;

void main()
{
    vec4 finalColor = color;
    if (hasSprite) finalColor *= texture(sprite, TexCoord).rgba;

    FragColor = finalColor;
} 