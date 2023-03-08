#pragma once

#include "Buffers/VertexArray.h"
#include "Shaders/Program.h"
#include "Textures/Texture.h"
#include <list>

class GPU
{
private:
    // buffers
    std::list<VertexBuffer> vertex_buffers;
    std::list<IndexBuffer> index_buffers;
    std::list<VertexArray> vertex_arrays;

    // shaders
    std::list<Shader> shaders;
    std::list<Program> programs;

    // textures
    std::list<Texture> textures;

public:
    // buffers
    VertexBufferHandle createVertexBuffer(const void *data, u32 size);
    IndexBufferHandle createIndexBuffer(const u32 *data, u32 size);
    IndexBufferHandle createIndexBuffer(const u16 *data, u32 size);
    VertexArrayHandle createVeretxArray();

    void destroy(VertexBufferHandle buffer);
    void destroy(IndexBufferHandle buffer);
    void destroy(VertexArrayHandle vertex_array);

    // shaders
    ShaderHandle createShader(char *source, Shader::Type type);
    ProgramHandle createProgram(const ShaderHandle vertex, const ShaderHandle fragment);
    ProgramHandle createProgram(const std::string &vertex_path, const std::string &fragment_path);

    void destroy(ShaderHandle shader);
    void destroy(ProgramHandle program);

    // textures
    TextureHandle createTexture(const Image &image, Format internal_format = Format::COUNT);
    TextureHandle createTexture(const std::string &image_path);

    void destroy(TextureHandle texture);

    GPU() = default;
    ~GPU();
};
