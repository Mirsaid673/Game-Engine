#pragma once

#include <GL/glew.h>
#include "Resource.h"

class Texture
{
public:
private:
    GLuint id = -1;
    i32 width;
    i32 height;
    u8 unit = 0;
    u8 mip_maps = 0;

public:
    Texture() = default;
    Texture(const Image &image, Format internal_format = Format::COUNT);

    void create(const Image &image, Format internal_format = Format::COUNT);
    void destroy();

    void bind() const;
    void unbind() const;
    void use() const;

    void wrapMode(WrapMode wp) const;
    void filter(Filter f) const;

    void setUnit(u8 value) { unit = value; }
    u8 getUnit() const { return unit; }

    i32 getWidth() const { return width; }
    i32 getHeight() const { return height; }

    bool operator==(const Texture &other) { return id == other.id; }
};

using TextureHandle = Texture *;