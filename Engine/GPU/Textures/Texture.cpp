#include "Texture.h"

#include "GLenums.h"

Texture::Texture(const Image &image,Format internal_format)
{
    create(image, internal_format);
}

void Texture::create(const Image &image, Format internal_format)
{
    width = image.width;
    height = image.height;

    if(internal_format == Format::COUNT)
        internal_format = image.format + Format::NON_SIZED_COUNT;

    glGenTextures(1, &id);
    bind();

    glTexStorage2D(GL_TEXTURE_2D, 1 + mip_maps, GL::translate(internal_format), width, height);

    if (image.data != nullptr)
        glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height, GL::translate(image.format), GL::translate(image.data_type), image.data);

    if (mip_maps)
        glGenerateMipmap(GL_TEXTURE_2D);

    unbind();
}

void Texture::wrapMode(WrapMode wp) const
{
    bind();

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL::translate(wp));
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL::translate(wp));

    unbind();
}

void Texture::filter(Filter f) const
{
    bind();

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL::translate(f));
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL::translate(f));

    unbind();
}

void Texture::bind() const
{
    glBindTexture(GL_TEXTURE_2D, id);
}

void Texture::unbind() const
{
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::use() const
{
    glActiveTexture(GL_TEXTURE0 + unit);
    bind();
}

void Texture::destroy()
{
    glDeleteTextures(1, &id);
    id = -1;
}