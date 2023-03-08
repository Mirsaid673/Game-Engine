#pragma once

class Texture;

using TextureHandle = Texture *;

struct Material
{
    TextureHandle diffuse_texture;
};