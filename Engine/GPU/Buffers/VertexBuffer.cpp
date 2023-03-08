#include "VertexBuffer.h"

#include <GL/glew.h>

VertexBuffer::VertexBuffer(const void *data, u32 size)
{
    create(data, size);
}

void VertexBuffer::create(const void *data, u32 size)
{
    this->size = size;
    glGenBuffers(1, &id);

    bind();
    glBufferData(GL_ARRAY_BUFFER, size, (GLvoid *)data, GL_STATIC_DRAW);
}

void VertexBuffer::bind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, id);
}

void VertexBuffer::unbind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBuffer::destroy()
{
    glDeleteBuffers(1, &id);
    id = -1;
}
