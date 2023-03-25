#pragma once

#include "Textures/Texture.h"

class Program;
using ProgramHandle = Program *;

struct Material
{
    enum TextureType
    {
        DIFFUSE,
        SPECULAR,
        COUNT,
    };

    ProgramHandle program;

    glm::vec3 color = glm::vec3(1);
    TextureHandle diffuse_map = nullptr;
    TextureHandle specular_map = nullptr;
    float shininess = 32.0f;
};