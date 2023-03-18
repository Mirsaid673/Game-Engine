#pragma once

#include <GL/glew.h>
#include "Resource.h"

class Texture
{
public:
private:
    GLuint id = -1;
    u32 width;
    u32 height;
    Format format;
    u8 unit = 0;
    u8 mip_maps = 0;

public:
    Texture() = default;
    Texture(const Image &image, u8 mip_maps_count = 0, Format internal_format = Format::COUNT);

    void create(const Image &image, u8 mip_maps_count = 0, Format internal_format = Format::COUNT);
    void destroy();

    void bind() const;
    void unbind() const;
    void use() const;

    void wrapMode(WrapMode wp) const;
    void filter(Filter f) const;

    void setUnit(u8 value) { unit = value; }
    u8 getUnit() const { return unit; }

    u32 getWidth() const { return width; }
    u32 getHeight() const { return height; }
    Format getFormat() const { return format; }

    bool operator==(const Texture &other) { return id == other.id; }

    GLuint getID() const { return id; }

    friend class Framebuffer;
};

using TextureHandle = Texture *;