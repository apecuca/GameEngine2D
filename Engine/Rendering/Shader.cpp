#include "Shader.hpp"

// Standard
#include <fstream>
#include <sstream>

// External
#include <glm/gtc/matrix_transform.hpp>
#include "stb_image.h"
#include "GLFW/glfw3.h"

// Engine
#include "../Window.hpp"
#include "../Behaviour/GameObject.hpp"
#include "../Debug.hpp"

Shader::Shader(const char* vertexFile, const char* fragmentFile, GameObject& _parent) :
    ID { 0 },
    gameObject { _parent }
{
    // Path translation
    std::string vertexPath = "../Shaders/" + static_cast<std::string>(vertexFile);
    std::string fragmentPath = "../Shaders/" + static_cast<std::string>(fragmentFile);

    // 1. retrieve the vertex/fragment source code from filePath
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;

    // ensure ifstream objects can throw exceptions:
    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        // open files
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);
        std::stringstream vShaderStream, fShaderStream;
        // read file's buffer contents into streams
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();
        // close file handlers
        vShaderFile.close();
        fShaderFile.close();
        // convert stream into string
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    }
    catch (std::ifstream::failure& e)
    {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ: " << e.what() << std::endl;
    }
    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();

    // 2. compile shaders
    GLuint vertex, fragment;
    // vertex shader
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex);
    CheckCompileErrors(vertex, "VERTEX");

    // fragment Shader
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);
    CheckCompileErrors(fragment, "FRAGMENT");

    // shader Program
    ID = glCreateProgram();
    glAttachShader(ID, vertex);
    glAttachShader(ID, fragment);
    glLinkProgram(ID);
    CheckCompileErrors(ID, "PROGRAM");

    // delete the shaders as they're linked into our program now and no longer necessary
    glDeleteShader(vertex);
    glDeleteShader(fragment);

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

    // Extra
    Use();
    SetVec4("color", 1.0f, 1.0f, 1.0f, 0.5f);
}

Shader::~Shader()
{
    // Delete all buffers and shader program to free memory
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteProgram(ID);
}

//
// Shader Utilities
//

// activate the shader
void Shader::Draw()
{
    // Bind program
    Use();

    float aspect = (float)Window::width / (float)Window::height;
    float fov = 5.0f;
    projMat = glm::ortho(-aspect * fov, aspect * fov, -1.0f * fov, 1.0f * fov, 0.0f, 100.0f);
    viewMat = glm::translate(viewMat, glm::vec3(0.0f, 0.0f, -10.0f));
    SetMat4("projection", projMat);
    SetMat4("view", viewMat);

    // Update model matrix
    // 
    modelMat = glm::translate(modelMat, gameObject.position);
    if (glm::length(gameObject.rotation) != 0)
    {
        modelMat = glm::rotate(modelMat,
            glm::radians(glm::length(gameObject.rotation)),
            glm::normalize(gameObject.rotation));
    }
    modelMat = glm::scale(modelMat, gameObject.scale);
    SetMat4("model", modelMat);

    // Textures
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureID);

    // Bind VAO and draw call
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    // Cleanup
    viewMat = glm::mat4(1.0f);
    projMat = glm::mat4(1.0f);
    modelMat = glm::mat4(1.0f);
}

//
// Texture handlers
//

GLuint Shader::LoadTextureFromFile(const std::string& file, bool gamma)
{
    std::string filePath = "../Resources/" + file;

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

    // Update uniforms
    SetInt("sprite", 0);
    SetBool("hasSprite", true);

    return textureID;
}

// utility uniform functions
// ------------------------------------------------------------------------
void Shader::Use() const
{
    glUseProgram(ID);
}
// ------------------------------------------------------------------------
void Shader::SetBool(const std::string& name, bool value) const
{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}
// ------------------------------------------------------------------------
void Shader::SetInt(const std::string& name, int value) const
{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}
// ------------------------------------------------------------------------
void Shader::SetFloat(const std::string& name, float value) const
{
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}
// ------------------------------------------------------------------------
void Shader::SetVec2(const std::string& name, const glm::vec2& value) const
{
    glUniform2fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
}
void Shader::SetVec2(const std::string& name, float x, float y) const
{
    glUniform2f(glGetUniformLocation(ID, name.c_str()), x, y);
}
// ------------------------------------------------------------------------
void Shader::SetVec3(const std::string& name, const glm::vec3& value) const
{
    glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
}
void Shader::SetVec3(const std::string& name, float x, float y, float z) const
{
    glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z);
}
// ------------------------------------------------------------------------
void Shader::SetVec4(const std::string& name, const glm::vec4& value) const
{
    glUniform4fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
}
void Shader::SetVec4(const std::string& name, float x, float y, float z, float w) const
{
    glUniform4f(glGetUniformLocation(ID, name.c_str()), x, y, z, w);
}
// ------------------------------------------------------------------------
void Shader::SetMat2(const std::string& name, const glm::mat2& mat) const
{
    glUniformMatrix2fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
// ------------------------------------------------------------------------
void Shader::SetMat3(const std::string& name, const glm::mat3& mat) const
{
    glUniformMatrix3fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
// ------------------------------------------------------------------------
void Shader::SetMat4(const std::string& name, const glm::mat4& mat) const
{
    glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

// utility function for checking shader compilation/linking errors.
void Shader::CheckCompileErrors(GLuint shader, std::string type)
{
    GLint success;
    GLchar infoLog[1024];
    if (type != "PROGRAM")
    {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
        }
    }
    else
    {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
        }
    }
}