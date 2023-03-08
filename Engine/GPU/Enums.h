#pragma once

#include "Core.h"

enum class DataType : u8
{
    BYTE,
    UNSIGNED_BYTE,
    SHORT,
    UNSIGNED_SHORT,
    INT,
    UNSIGNED_INT,
    FLOAT,
    DOUBLE,
    COUNT,
};

enum class Format : u8
{
    RED,
    RG,
    RGB,
    RGBA,

    NON_SIZED_COUNT,

    RED8 = NON_SIZED_COUNT,
    RG8,
    RGB8,
    RGBA8,

    RED8I,
    RG8I,
    RGB8I,
    RGBA8I,

    RED8UI,
    RG8UI,
    RGB8UI,
    RGBA8UI,

    SRGB8,
    SRGBA8,

    COUNT,
};

enum class WrapMode : u8
{
    REPEAT,
    MIRRORED_REPEAT,
    CLAMP,
    CLAMP_TO_EDGE,

    COUNT,
};

enum class Filter : u8
{
    NEAREST,
    LINEAR,

    NEAREST_MIPMAP_NEAREST,
    LINEAR_MIPMAP_LINEAR,
    LINEAR_MIPMAP_NEAREST,
    NEAREST_MIPMAP_LINEAR,

    COUNT,
};

enum class Primitive : u8
{
    POINTS,

    LINES,
    LINE_STRIP,
    LINE_LOOP,

    TRIANGLES,
    TRIANGLE_STRIP,
    TRIANGLE_FAN,

    COUNT,
};

template <typename T>
T operator+(T l, T r)
{
    return (T)((u8)l + (u8)r);
}

template <typename T>
T operator+(u8 l, T r)
{
    return (T)(l + (u8)r);
}

template <typename T>
T operator+(T l, u8 r)
{
    return (T)(u8(l) + r);
}