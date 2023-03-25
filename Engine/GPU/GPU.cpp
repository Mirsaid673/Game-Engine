#include "GPU.h"

VertexBufferHandle GPU::createVertexBuffer(const void *data, u32 size)
{
    vertex_buffers.emplace_back(data, size);
    return &vertex_buffers.back();
}

IndexBufferHandle GPU::createIndexBuffer(const u32 *data, u32 size)
{
    index_buffers.emplace_back(data, size);
    return &index_buffers.back();
}

IndexBufferHandle GPU::createIndexBuffer(const u16 *data, u32 size)
{
    index_buffers.emplace_back(data, size);
    return &index_buffers.back();
}

VertexArrayHandle GPU::createVeretxArray()
{
    VertexArray va;
    va.create();
    vertex_arrays.push_back(va);
    return &vertex_arrays.back();
}

void GPU::destroy(VertexBufferHandle buffer)
{
    vertex_buffers.remove(*buffer);
    buffer->destroy();
}

void GPU::destroy(IndexBufferHandle buffer)
{
    index_buffers.remove(*buffer);
    buffer->destroy();
}

void GPU::destroy(VertexArrayHandle vertex_array)
{
    vertex_arrays.remove(*vertex_array);
    vertex_array->destroy();
}

//=======shaders========

ShaderHandle GPU::createShader(char *source, Shader::Type type)
{
    shaders.emplace_back(source, type);
    return &shaders.back();
}

ProgramHandle GPU::createProgram(const ShaderHandle vertex, const ShaderHandle fragment)
{
    programs.emplace_back(vertex, fragment);
    return &programs.back();
}

ProgramHandle GPU::createProgram(const std::string &vertex_path, const std::string &fragment_path)
{
    programs.emplace_back(vertex_path, fragment_path);
    return &programs.back();
}

void GPU::destroy(ShaderHandle shader)
{
    shaders.remove(*shader);
    shader->destroy();
}

void GPU::destroy(ProgramHandle program)
{
    programs.remove(*program);
    program->destroy();
}

//=======textures========

TextureHandle GPU::createTexture(const Image &image, u8 mip_maps_count, Format internal_format)
{
    textures.emplace_back(image, mip_maps_count, internal_format);
    return &textures.back();
}

TextureHandle GPU::createTexture(const std::string &image_path, u8 mip_maps_count)
{
    Image image = Resource::loadImage(image_path);
    textures.emplace_back(image, mip_maps_count);
    Resource::freeImage(image);

    return &textures.back();
}

void GPU::destroy(TextureHandle texture)
{
    textures.remove(*texture);
    texture->destroy();
}

FramebufferHandle GPU::createFramebuffer(u32 width, u32 height)
{
    framebuffers.emplace_back(width, height);
    return &framebuffers.back();
}

void GPU::destroy(FramebufferHandle framebuffer)
{
    framebuffers.remove(*framebuffer);
    framebuffer->destroy();
}

//=======mesh========

VertexArrayHandle GPU::loadMesh(const Mesh &mesh)
{
    VertexArrayHandle res = createVeretxArray();

    VertexBufferHandle pos = createVertexBuffer(mesh.positions.data(), mesh.positions.size() * sizeof(glm::vec3));
    res->linkAttribs(pos, {Attrib::Location::POSITION});

    if (mesh.normals.size() != 0)
    {
        VertexBufferHandle normal = createVertexBuffer(mesh.normals.data(), mesh.normals.size() * sizeof(glm::vec3));
        res->linkAttribs(normal, {{Attrib::Location::NORMAL}});
    }

    if (mesh.tex_coords0.size() != 0)
    {
        VertexBufferHandle tex_coord = createVertexBuffer(mesh.tex_coords0.data(), mesh.tex_coords0.size() * sizeof(glm::vec2));
        res->linkAttribs(tex_coord, {{Attrib::Location::TEX_COORD0, 2}});
    }

    IndexBufferHandle ibo = createIndexBuffer(mesh.indices.data(), mesh.indices.size() * sizeof(u32));
    res->linkIndexBuffer(ibo);

    return res;
}

//=======================
void GPU::cleanup()
{
    // destroying buffers
    for (auto &buffer : vertex_buffers)
        buffer.destroy();

    for (auto &buffer : index_buffers)
        buffer.destroy();

    for (auto &vertex_array : vertex_arrays)
        vertex_array.destroy();

    // desrtoying shaders
    for (auto &shader : shaders)
        shader.destroy();

    for (auto &program : programs)
        program.destroy();

    // textures
    for (auto &texture : textures)
        texture.destroy();

    for (auto &framebuffer : framebuffers)
        framebuffer.destroy();
}
