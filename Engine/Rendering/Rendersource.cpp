#include "Rendersource.hpp"

// Engine 
#include "Rendering.hpp"
#include "../Window.hpp"
#include "../Debug.hpp"
#include "Shader.hpp"
#include "../Behaviour/GameObject.hpp"

#include <glm/gtc/matrix_transform.hpp>

RenderSource::RenderSource(GameObject& parent) : Component(parent),
	color(glm::vec4(1.0f)), 
    VAO{0}, VBO{0}, EBO{0},
    modelMat{glm::mat4(1.0f)}, projMat{glm::mat4(1.0f)}, viewMat{glm::mat4(1.0f)}
{
	Rendering::AddRenderSource(this);
}

RenderSource::~RenderSource()
{
	Rendering::RemoveRenderSource(this);

    // Delete all buffers to free memory
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

void RenderSource::Render()
{
	if (shader == NULL) return;
	
	// Update shader settings
	shader->SetVec4("color", color);

	//shader->Draw(currentSpriteId);
    // Bind program
    shader->Use();

    const Sprite& currentSprite = Rendering::GetPooledSprite(currentSpriteId);

    // Update sprite's size on shader
    shader->SetIVec2("texSize", currentSprite.getSize());

    // Proj and view matrix
    float aspect = (float)Window::width / (float)Window::height;
    float fov = 5.0f;
    projMat = glm::ortho(-aspect * fov, aspect * fov, -1.0f * fov, 1.0f * fov, 0.0f, 100.0f);
    viewMat = glm::translate(viewMat, glm::vec3(0.0f, 0.0f, -10.0f));
    shader->SetMat4("projection", projMat);
    shader->SetMat4("view", viewMat);

    // Update model matrix
    // 
    modelMat = glm::translate(modelMat, gameObject.position);
    if (glm::length(gameObject.rotation) != 0)
    {
        modelMat = glm::rotate(modelMat,
            glm::radians(glm::length(gameObject.rotation)),
            glm::normalize(gameObject.rotation));
    }
    // Sprite size
    glm::vec3 spriteSize = glm::vec3(currentSprite.getSize(), 1.0f) / currentSprite.pixelsPerUnit;
    spriteSize.z = 1.0f;
    modelMat = glm::scale(modelMat, spriteSize);
    // GameObject scale
    modelMat = glm::scale(modelMat, gameObject.scale);
    shader->SetMat4("model", modelMat);

    // Textures
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, currentSprite.getTexID());

    // Bind VAO and draw call
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    // Cleanup
    viewMat = glm::mat4(1.0f);
    projMat = glm::mat4(1.0f);
    modelMat = glm::mat4(1.0f);
}

void RenderSource::InitShader(const char* vertex, const char* fragment)
{
	if (shader != nullptr)
	{
		Debug::Log("Shader already initialized!");
		return;
	}

	shader = std::make_unique<Shader>(vertex, fragment);

    // Basic vertices
    float vertices[] = {
        // positions            // texture coords
        1.0f,  1.0f, 0.0f,      1.0f, 1.0f, // top right
        1.0f, -1.0f, 0.0f,      1.0f, 0.0f, // bottom right
       -1.0f, -1.0f, 0.0f,      0.0f, 0.0f, // bottom left
       -1.0f,  1.0f, 0.0f,      0.0f, 1.0f  // top left 
    };

    GLuint indices[] = {  // note that we start from 0!
        0, 1, 3,  // first Triangle
        1, 2, 3   // second Triangle
    };

    // Create and link VAO and VBO
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    // Bind VAO for use
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Unbind stuff
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void RenderSource::SetRenderOrder(const int& value)
{
	renderOrder = value;
	Rendering::OnRenderOrderChanged();
}