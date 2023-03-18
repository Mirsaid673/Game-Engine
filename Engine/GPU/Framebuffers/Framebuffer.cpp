#include "Framebuffer.h"
#include "Log.h"

GLuint Framebuffer::current = 0;

Framebuffer::Framebuffer(u32 width, u32 height)
{
    create(width, height);
}

void Framebuffer::create(u32 width, u32 height)
{
    glGenFramebuffers(1, &id);
    glBindFramebuffer(GL_FRAMEBUFFER, id);

    // binding texture
    texture.create({nullptr, width, height, Format::RGB});
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture.id, 0);

    // binding renderbuffer
    createRenderBuf();
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        Log::error("could not create framebuffer");
    glBindFramebuffer(GL_FRAMEBUFFER, current);
};

void Framebuffer::resize(u32 width, u32 height)
{
    glBindFramebuffer(GL_FRAMEBUFFER, id);

    texture.destroy();
    texture.create({nullptr, width, height, Format::RGB});
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture.id, 0);

    glBindRenderbuffer(GL_RENDERBUFFER, rbo);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);

    glBindFramebuffer(GL_FRAMEBUFFER, current);
}

void Framebuffer::createRenderBuf()
{
    glGenRenderbuffers(1, &rbo);
    glBindRenderbuffer(GL_RENDERBUFFER, rbo);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, texture.width, texture.height);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
}

void Framebuffer::destroyRenderBuf()
{
    glDeleteRenderbuffers(1, &rbo);
    rbo = -1;
}

void Framebuffer::destroy()
{
    texture.destroy();
    destroyRenderBuf();
    glDeleteFramebuffers(1, &id);
    id = -1;
}

void Framebuffer::bind() const
{
    current = id;
    glBindFramebuffer(GL_FRAMEBUFFER, id);
}

void Framebuffer::unbind() const
{
    current = 0;
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Framebuffer::bindMain()
{
    current = 0;
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}