#pragma once

#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexLayout.h"

class VertexArray
{
private:
    GLuint id = -1;
    u32 vertex_count = 0;
    u32 index_count = 0;
    Primitive primitive = Primitive::TRIANGLES;
    DataType index_data_type;

public:
    void linkAttribs(const VertexBufferHandle vertex_buffer,
                     const VertexLayout &vertex_attribs,
                     bool AOS = true);
    // AOS - array of structure:
    // [a1, a2, a3], [a1, a2, a3] ...
    // SOA - structure 0f array
    // [a1, a1, a1, ...], [a2, a2, a2, ...]
    // a - attribute

    void linkIndexBuffer(const IndexBufferHandle index_buffer);

    void create();
    void destroy();

    void bind() const;
    void unbind() const;

    u32 getIndexCount() const { return index_count; }
    Primitive getPrimitive() const { return primitive; }
    DataType getIndexDataType() const { return index_data_type; }

    bool operator==(const VertexArray &other) const { return id == other.id; }
};

using VertexArrayHandle = VertexArray *;