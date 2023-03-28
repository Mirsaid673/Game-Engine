#pragma once

#include "Textures/Texture.h"
#include <bitset>

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

    std::bitset<2> texture_mask; // 0 bit - diffuse
                                 // 1 bit - specular

    void setDiffuse(TextureHandle texture)
    {
        diffuse_map = texture;
        texture->setUnit(DIFFUSE);
        texture_mask.set(DIFFUSE);
    }

    void setSpecular(TextureHandle texture)
    {
        specular_map = texture;
        texture->setUnit(SPECULAR);
        texture_mask.set(SPECULAR);
    }
};