#pragma once

#include "Textures/Texture.h"

class Framebuffer
{
private:
    Texture texture;
    GLuint id = -1;
    GLuint rbo = -1;

public:
    Framebuffer() = default;
    Framebuffer(u32 width, u32 height);

    void create(u32 width, u32 height);
    void destroy();

    void bind() const;
    void unbind() const;

    void resize(u32 width, u32 height);
    void resize(const glm::uvec2 &size) { resize(size.x, size.y); }

    u32 getWidth() const { return texture.width; }
    u32 getHeight() const { return texture.height; }
    glm::uvec2 getSize() const { return {texture.width, texture.height}; }

    TextureHandle getTexture() { return &texture; }
    GLuint getTexID() const { return texture.getID(); }

    bool operator==(const Framebuffer &other) { return id == other.id; }

    static void bindMain();

private:
    void createRenderBuf();
    void destroyRenderBuf();
    static GLuint current;
};

using FramebufferHandle = Framebuffer *;