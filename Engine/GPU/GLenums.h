#pragma once

#include "Enums.h"
#include "Textures/Texture.h"

#include <GL/glew.h>
namespace GL
{
    GLenum translate(DataType t);
    GLenum translate(Format format);
    GLenum translate(WrapMode wrap_mode);
    GLenum translate(Filter filter);
    GLenum translate(Primitive pr);
}