#pragma once
#include <glm/glm.hpp>
#include "Mesh.hpp"
#include "Texture.hpp"
#include "Shader.hpp"

class GameObject {
public:
    GameObject(Mesh* mesh, Texture* tex, Shader* shader);
    void Draw(const glm::mat4& view, const glm::mat4& proj);

    glm::vec3 position;
    float size = 1.0f;
    bool isActive = true; 

private:
    Mesh* mesh;
    Texture* tex;
    Shader* shader;
};