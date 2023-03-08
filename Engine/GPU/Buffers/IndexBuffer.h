#pragma once

#include "Core.h"
#include "Enums.h"
#include <GL/glew.h>

class IndexBuffer
{
private:
    GLuint id = -1;
    DataType data_type;
    u32 index_count = 0;

public:
    IndexBuffer() = default;
    IndexBuffer(const u32 *data, u32 size);
    IndexBuffer(const u16 *data, u32 size);

    void create(const u32 *data, u32 size);
    void create(const u16 *data, u32 size);
    void destroy();

    void bind() const;
    void unbind() const;

    u32 getIndexCount() const { return index_count; }
    DataType getDataType() const { return data_type; }

    bool operator==(const IndexBuffer &other) const { return id == other.id; }
};

using IndexBufferHandle = IndexBuffer *;