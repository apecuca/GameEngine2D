#include "Rendering.hpp"

// Standard
#include <algorithm>

// Externals
#include "stb_image.h"

// Engine
#include "../Debug.hpp"
#include "Shader.hpp"
#include "../Window.hpp"

// Statics
std::vector<RenderSource*> Rendering::renderSources;

GLuint Rendering::FBO, Rendering::FBT, Rendering::RBO;
GLuint Rendering::screenquadVAO, Rendering::screenquadVBO;
std::unique_ptr<Shader> Rendering::screenShader;

std::vector<std::unique_ptr<Sprite>> Rendering::pooledSprites;

void Rendering::Init()
{
    // Inicializar shader da tela
    screenShader = std::make_unique<Shader>("framebuffer.vert", "framebuffer.frag");

    GenerateBuffers();

    // Atualizar shader
    screenShader->Use();
    // Bindar textura
    screenShader->SetInt("screenTexture", 0);
    // Variáveis inicials
    screenShader->SetInt("screenWidth", Window::width);
    screenShader->SetInt("screenHeight", Window::height);

    // Pool default sprite
    PoolSprite("Default.png", 32);
}

void Rendering::Render(std::unique_ptr<Window>& window)
{
	// Bindar framebuffer
	glBindFramebuffer(GL_FRAMEBUFFER, FBO);

	// Habilitar depth test para desenhar objetos
	//glEnable(GL_DEPTH_TEST);

	window->ClearWindow();

	// Render all enabled sources
	for (int i = 0; i < renderSources.size(); i++)
	{
		if (!renderSources.at(i)->enabled) continue;

		renderSources.at(i)->Render();
	}

	// Desbindar framebuffer e limpar janela
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	// Desabilitar depth test para desenhar quad
	//glDisable(GL_DEPTH_TEST);

	// Bindar shader e desenhar quad
	screenShader->Use();
	glBindVertexArray(screenquadVAO);
	glBindTexture(GL_TEXTURE_2D, FBT);
	glDrawArrays(GL_TRIANGLES, 0, 6);

	// Inverter os buffers de vídeo
	window->SwapBuffers();
}

void Rendering::AddRenderSource(RenderSource* source)
{
	renderSources.emplace_back(source);
}

void Rendering::RemoveRenderSource(RenderSource* source)
{
	for (int i = 0; i < renderSources.size(); i++)
	{
		if (renderSources.at(i) != source)
			continue;

		renderSources.erase(renderSources.begin() + i);
	}
}

int Rendering::PoolSprite(const char* fileName, float pixelsPerUnit)
{
    // Emplace the new sprite id on the back
    pooledSprites.push_back(
        std::make_unique<Sprite>(fileName, pixelsPerUnit));
        //LoadTextureFromFile(fileName, false));

    // Return id of the newly emplaced sprite
    return static_cast<int>(pooledSprites.size() - 1);
}

const Sprite& Rendering::GetPooledSprite(const int& id)
{
    // If it's not a valid ID, return default texture
	if (id >= pooledSprites.size() || id < 0)
		throw std::runtime_error("No sprite with index " + std::to_string(id));

    return *pooledSprites[id];
}

void Rendering::ClearSpritePool()
{
    pooledSprites.clear();
}

void Rendering::GenerateBuffers()
{
	// Frame buffer object
	glGenFramebuffers(1, &FBO);
	glBindFramebuffer(GL_FRAMEBUFFER, FBO);

	// Gerar e configurar FBT (Frame buffer texture)
	glGenTextures(1, &FBT);
	glBindTexture(GL_TEXTURE_2D, FBT);
	// Gerar textura
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, Window::width, Window::height,
		0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	// Parâmetros
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	// Atribuir a textura bindada para o frame buffer
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, FBT, 0);

	// Gerar e configurar RBO (Render buffer object)
	glGenRenderbuffers(1, &RBO);
	glBindRenderbuffer(GL_RENDERBUFFER, RBO);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, Window::width, Window::height);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, RBO);

	auto fboStatus = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	if (fboStatus != GL_FRAMEBUFFER_COMPLETE)
		Debug::Log("FRAMEBUFFER ERROR:: " + std::to_string(fboStatus));

	//
	// TEXTURA e Quad
	//

	float quadVertices[] = { // vertex attributes for a quad that fills the entire screen in Normalized Device Coordinates.
		// positions   // texCoords
		-1.0f,  1.0f,  0.0f, 1.0f,
		-1.0f, -1.0f,  0.0f, 0.0f,
		 1.0f, -1.0f,  1.0f, 0.0f,

		-1.0f,  1.0f,  0.0f, 1.0f,
		 1.0f, -1.0f,  1.0f, 0.0f,
		 1.0f,  1.0f,  1.0f, 1.0f
	};

	// Gerar VAO e VBO do quad da tela
	glGenVertexArrays(1, &screenquadVAO);
	glGenBuffers(1, &screenquadVBO);
	glBindVertexArray(screenquadVAO);
	glBindBuffer(GL_ARRAY_BUFFER, screenquadVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));

	// Desbindar tudo
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Rendering::OnRenderOrderChanged()
{
	// std::sort's algorith sorts everything inside the vector
	// In the future, I'll rewrite this with a custom algorith to sort
	// only the changed source
	std::sort(std::begin(renderSources), std::end(renderSources),
		[](const RenderSource* vecA, const RenderSource* vecB) -> bool {
			return vecA->GetRenderOrder() < vecB->GetRenderOrder();
		});
}

void Rendering::ResizeFramebuffer()
{
	if (screenShader == nullptr)
		return;

	// Atualizar a textura do framebuffer (Framebuffer Texture/FBT)
	glBindTexture(GL_TEXTURE_2D, FBT);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, Window::width, Window::height,
		0, GL_RGB, GL_UNSIGNED_BYTE, NULL);

	// Atualizar objeto de renderização (Renderbuffer Object/RBO)
	glBindRenderbuffer(GL_RENDERBUFFER, RBO);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, Window::width, Window::height);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, RBO);

	// Desbindar usados
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);

	// Atualizar tamanho da tela no shader
	screenShader->Use();
	screenShader->SetInt("screenWidth", Window::width);
	screenShader->SetInt("screenHeight", Window::height);
}