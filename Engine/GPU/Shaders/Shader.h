#pragma once

#include <GL/glew.h>

class Shader
{
private:
    GLuint id = -1;

public:
    enum Type
    {
        VERTEX,
        FRAGMENT,
        MAX,
    };

private:
    void compileInfo();

public:
    Shader() = default;
    Shader(const char *code, Type type);

    void create(const char *code, Type type);
    void destroy();

    bool operator==(const Shader &other) const { return id == other.id; }

    friend class Program;
};

using ShaderHandle = Shader *;