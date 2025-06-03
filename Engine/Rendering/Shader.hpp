#pragma once

// Standard libraries
#include <iostream>

// External libraries
#include "../CommonInclude/CommonRender.hpp"
#include "glm/glm.hpp"

// Forward
class GameObject;

class Shader
{
public:
    Shader(
        const char* vertexFile,
        const char* fragmentFile,
        GameObject& _parent);
    ~Shader();

    // Bind shader ID
    void Draw(const int spriteId);

    // Compilation error checks
    static void CheckCompileErrors(GLuint shader, std::string type);

    //
    // Shader utilities
    //

    // Shader uniform functions
    void Use() const;
    void SetBool(const std::string& name, bool value) const;
    void SetInt(const std::string& name, int value) const;
    void SetFloat(const std::string& name, float value) const;
    void SetIVec2(const std::string& name, const glm::ivec2& value) const;
    void SetVec2(const std::string& name, const glm::vec2& value) const;
    void SetVec2(const std::string& name, float x, float y) const;
    void SetVec3(const std::string& name, const glm::vec3& value) const;
    void SetVec3(const std::string& name, float x, float y, float z) const;
    void SetVec4(const std::string& name, const glm::vec4& value) const;
    void SetVec4(const std::string& name, float x, float y, float z, float w) const;
    void SetMat2(const std::string& name, const glm::mat2& mat) const;
    void SetMat3(const std::string& name, const glm::mat3& mat) const;
    void SetMat4(const std::string& name, const glm::mat4& mat) const;

private:
    // Shader's ID
    GLuint ID;
    // Buffers
    GLuint VAO, VBO, EBO;

    // Transformation matrices
    glm::mat4 viewMat, projMat, modelMat;

    // GameObject this shader is attached to
    GameObject& gameObject;
    
};