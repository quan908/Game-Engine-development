#pragma once
#include <GL/glew.h>
#include <vector>

class Mesh {
public:
    Mesh(const float* vertices, size_t vSize, const unsigned int* indices, size_t iSize);
    void Draw() const;
private:
    GLuint VAO, VBO, EBO;
};
