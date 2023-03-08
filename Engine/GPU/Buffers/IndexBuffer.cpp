#include "IndexBuffer.h"

#include <GL/glew.h>

IndexBuffer::IndexBuffer(const u32 *data, u32 size)
{
    create(data, size);
}

IndexBuffer::IndexBuffer(const u16 *data, u32 size)
{
    create(data, size);
}

void IndexBuffer::create(const u32 *data, u32 size)
{
    data_type = DataType::UNSIGNED_INT;
    index_count = size / sizeof(u32);

    glGenBuffers(1, &id);

    bind();
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, (GLvoid *)data, GL_STATIC_DRAW);
}

void IndexBuffer::create(const u16 *data, u32 size)
{
    data_type = DataType::UNSIGNED_SHORT;
    index_count = size / sizeof(u16);

    glGenBuffers(1, &id);

    bind();
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, (GLvoid *)data, GL_STATIC_DRAW);
}

void IndexBuffer::bind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
}

void IndexBuffer::unbind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void IndexBuffer::destroy()
{
    glDeleteBuffers(1, &id);
    id = -1;
}
