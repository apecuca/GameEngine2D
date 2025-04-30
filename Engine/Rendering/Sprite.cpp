#include "Sprite.hpp"

// Externals
#include "stb_image.h"

#include "../Debug.hpp"

Sprite::Sprite(const char* _fileName, float _pixelsPerUnit) :
    texId(0), fileName(_fileName), pixelsPerUnit(_pixelsPerUnit)
{
    std::string filePath("Resources/Images/" + (std::string)_fileName);

    glGenTextures(1, &texId);
    glBindTexture(GL_TEXTURE_2D, texId);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    stbi_set_flip_vertically_on_load(true);

    int nrComponents;
    unsigned char* data = stbi_load(filePath.c_str(), &width, &height, &nrComponents, 0);
    if (data)
    {
        GLenum format = GL_RGB;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;
        else Debug::Log("Unsupported format type");

        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

    }
    else {
        Debug::Log("Texture failed to load at path: " + filePath);
    }

    // Unbind textura
    glBindTexture(GL_TEXTURE_2D, 0);

    // Free space
    stbi_image_free(data);
}

Sprite::~Sprite()
{
    glDeleteTextures(1, &texId);
}