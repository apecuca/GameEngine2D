#version 330 core

out vec4 FragColor;

in vec2 TexCoord;

uniform vec4 color;

// Sprite animation handling
uniform sampler2D sprite;

void main()
{
    FragColor = texture(sprite, TexCoord).rgba * color;
} 