#pragma once
#include <vector>
#include "GameObject.hpp"

class SceneManager {
public:
    void Add(GameObject* obj);
    void DrawAll(const glm::mat4& view, const glm::mat4& proj);
    std::vector<GameObject*> objects;
};
