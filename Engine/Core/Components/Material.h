#pragma once

#include "Textures/Texture.h"
#include "Shaders/Program.h"

struct Material
{
    ProgramHandle program;

    TextureHandle diffuse_texture;
};