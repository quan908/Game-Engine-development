#include "GameObject.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

GameObject::GameObject(Mesh* m, Texture* t, Shader* s)
    : mesh(m), tex(t), shader(s), position(0.0f), isActive(true) { }

void GameObject::Draw(const glm::mat4& view, const glm::mat4& proj) 
    {

    if (!isActive) 
    {
        return;
    }

    shader->Use();
    tex->Bind();

    glm::mat4 model = glm::translate(glm::mat4(1.0f), position);
    model = glm::scale(model, glm::vec3(size));

    glUniformMatrix4fv(glGetUniformLocation(shader->ID, "model"), 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(glGetUniformLocation(shader->ID, "view"), 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(glGetUniformLocation(shader->ID, "projection"), 1, GL_FALSE, glm::value_ptr(proj));
    glUniform1i(glGetUniformLocation(shader->ID, "mytexture"), 0);

    mesh->Draw();
}