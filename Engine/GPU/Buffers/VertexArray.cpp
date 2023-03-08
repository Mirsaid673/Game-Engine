#include "VertexArray.h"
#include "GLenums.h"

void VertexArray::linkAttribs(const VertexBufferHandle vertex_buffer,
                              const VertexLayout &vertex_attribs,
                              bool AOS)
{
    u32 vertex_size_in_bytes = 0;
    u32 offset = 0;
    u32 stride = 0;

    for (auto attrib : vertex_attribs)
        vertex_size_in_bytes += attrib.getSize();

    if (AOS)
        for (auto attrib : vertex_attribs)
            stride += attrib.getSize();

    vertex_count = vertex_buffer->getSize() / vertex_size_in_bytes;
    bind();
    vertex_buffer->bind();

    for (auto attrib : vertex_attribs)
    {
        glEnableVertexAttribArray((u8)attrib.getLocation());
        glVertexAttribPointer((u8)attrib.getLocation(), attrib.getCount(), GL::translate(attrib.getDataType()), attrib.getNormalized(), stride, reinterpret_cast<GLvoid *>(offset));

        if (AOS)
            offset += attrib.getSize();
        else
            offset += vertex_count * attrib.getSize();
    }

    unbind();
    vertex_buffer->unbind();
}

void VertexArray::linkIndexBuffer(const IndexBufferHandle index_buffer)
{
    index_count = index_buffer->getIndexCount();
    index_data_type = index_buffer->getDataType();

    bind();
    index_buffer->bind();
    unbind();
}

void VertexArray::create()
{
    glGenVertexArrays(1, &id);
}

void VertexArray::destroy()
{
    glDeleteVertexArrays(1, &id);
    id = -1;
}

void VertexArray::bind() const
{
    glBindVertexArray(id);
}

void VertexArray::unbind() const
{
    glBindVertexArray(0);
}
