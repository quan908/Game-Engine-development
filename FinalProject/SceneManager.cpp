#include "SceneManager.hpp"

void SceneManager::Add(GameObject* obj) {
    objects.push_back(obj);
}

void SceneManager::DrawAll(const glm::mat4& view, const glm::mat4& proj) {
    for (auto obj : objects)
        obj->Draw(view, proj);
}
