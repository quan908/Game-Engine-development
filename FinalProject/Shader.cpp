#include "Shader.hpp"
#include <iostream>

Shader::Shader(const char* vertexSrc, const char* fragmentSrc) {
    auto compile = [](GLenum type, const char* source) {
        GLuint shader = glCreateShader(type);
        glShaderSource(shader, 1, &source, NULL);
        glCompileShader(shader);
        return shader;
        };
    GLuint vShader = compile(GL_VERTEX_SHADER, vertexSrc);
    GLuint fShader = compile(GL_FRAGMENT_SHADER, fragmentSrc);
    ID = glCreateProgram();
    glAttachShader(ID, vShader);
    glAttachShader(ID, fShader);
    glLinkProgram(ID);
    glDeleteShader(vShader);
    glDeleteShader(fShader);
}

void Shader::Use() const {
    glUseProgram(ID);
}
