#pragma once
#include <string>
#include <GL/glew.h>

class Shader {
public:
    Shader(const char* vertexSrc, const char* fragmentSrc);
    void Use() const;
    GLuint ID;
};

