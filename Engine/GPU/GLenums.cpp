#include "GLenums.h"

namespace GL
{
    GLenum translate(DataType t)
    {
        static const GLenum tr[]{
            GL_BYTE,
            GL_UNSIGNED_BYTE,
            GL_SHORT,
            GL_UNSIGNED_SHORT,
            GL_INT,
            GL_UNSIGNED_INT,
            GL_FLOAT,
            GL_DOUBLE,
        };
        return tr[(u8)t];
    }

    GLenum translate(Format format)
    {
        static const GLenum tr[]{
            GL_RED,
            GL_RG,
            GL_RGB,
            GL_RGBA,

            GL_R8,
            GL_RG8,
            GL_RGB8,
            GL_RGBA8,

            GL_R8I,
            GL_RG8I,
            GL_RGB8I,
            GL_RGBA8I,

            GL_R8UI,
            GL_RG8UI,
            GL_RGB8UI,
            GL_RGBA8UI,

            GL_SRGB8,
            GL_SRGB8_ALPHA8,
        };
        return tr[(u8)format];
    }

    GLenum translate(WrapMode wrap_mode)
    {
        static const GLenum tr[]{
            GL_REPEAT,
            GL_MIRRORED_REPEAT,
            GL_CLAMP,
            GL_CLAMP_TO_EDGE,
        };
        return tr[(u8)wrap_mode];
    }

    GLenum translate(Filter filter)
    {
        static const GLenum tr[]{
            GL_NEAREST,
            GL_LINEAR,

            GL_NEAREST_MIPMAP_NEAREST,
            GL_LINEAR_MIPMAP_LINEAR,
            GL_LINEAR_MIPMAP_NEAREST,
            GL_NEAREST_MIPMAP_LINEAR,
        };
        return tr[(u8)filter];
    }

    GLenum translate(Primitive pr)
    {
        static const GLenum tr[]{
            GL_POINTS,

            GL_LINES,
            GL_LINE_STRIP,
            GL_LINE_LOOP,

            GL_TRIANGLES,
            GL_TRIANGLE_STRIP,
            GL_TRIANGLE_FAN,
        };
        return tr[(u8)pr];
    }
}