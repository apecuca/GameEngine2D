#include "Rendering.hpp"

// Externals
#include "stb_image.h"

// Engine
#include "../Debug.hpp"

// Statics
std::vector<std::reference_wrapper<RenderSource>> Rendering::renderSources;
std::vector<GLuint> Rendering::pooledSprites;

void Rendering::Init()
{
    // Pool default sprite
    PoolSprite("Default.png");
}

void Rendering::Render()
{
	// Render all enabled sources
	for (int i = 0; i < renderSources.size(); i++)
	{
		if (!renderSources.at(i).get().enabled) continue;

		renderSources.at(i).get().Render();
	}
}

void Rendering::AddRenderSource(RenderSource& source)
{
	renderSources.emplace_back(source);
}

void Rendering::RemoveRenderSource(RenderSource& source)
{
	for (int i = 0; i < renderSources.size(); i++)
	{
		if (renderSources.at(i) != source)
			continue;

		renderSources.erase(renderSources.begin() + i);
	}
}

int Rendering::PoolSprite(const char* fileName)
{
    // Emplace the new sprite id on the back
    pooledSprites.emplace_back(
        LoadTextureFromFile(fileName, false));

    // Return id of the newly emplaced sprite
    return (pooledSprites.size() - 1);
}

GLuint Rendering::GetPooledSprite(const int& id)
{
    // If it's not a valid ID, return default texture
    if (id >= pooledSprites.size() || id < 0)
        return 0;

    return pooledSprites[id];
}

void Rendering::ClearSpritePool()
{
    for (int i = pooledSprites.size() - 1; i >= 0; i--)
    {
        glDeleteTextures(1, &pooledSprites[i]);
    }
}

GLuint Rendering::LoadTextureFromFile(const std::string& file, bool gamma)
{
    std::string filePath = "../Resources/" + file;

    GLuint textureID;

    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    stbi_set_flip_vertically_on_load(true);

    int width, height, nrComponents;
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
    else
    {
        std::cout << "Texture failed to load at path: " << filePath << std::endl;
    }

    // Unbind textura
    glBindTexture(GL_TEXTURE_2D, 0);

    // Free space
    stbi_image_free(data);

    return textureID;
}