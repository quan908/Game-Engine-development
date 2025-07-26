#pragma once
#include <GL/glew.h>
#include <string>

class Texture {
public:
    Texture(const char* path);
    void Bind() const;
    GLuint ID;
};
