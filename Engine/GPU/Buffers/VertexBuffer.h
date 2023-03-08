#pragma once

#include "Core.h"
#include <GL/glew.h>

class VertexBuffer
{
private:
    GLuint id = -1;
    u32 size = 0;

public:
    VertexBuffer() = default;
    VertexBuffer(const void *data, u32 size);

    void create(const void *data, u32 size);
    void destroy();

    void bind() const;
    void unbind() const;

    u32 getSize() const { return size; }

    bool operator==(const VertexBuffer &other) const { return id == other.id; }
};

using VertexBufferHandle = VertexBuffer *;