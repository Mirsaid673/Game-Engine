#pragma once

#include "Shader.h"

#include <string>
#include <glm/glm.hpp>

class Program
{
private:
    GLuint id = -1;

    void linkInfo() const;

public:
    Program() = default;
    Program(const ShaderHandle vert, const ShaderHandle frag);
    Program(const std::string &vs_file, const std::string &fs_file);

    void create();
    void create(const ShaderHandle vert, const ShaderHandle frag);
    void create(const std::string &vs_file, const std::string &fs_file);
    void destroy();
    void attachShader(const ShaderHandle shader) const;
    void link() const;

    void use() const;
    void unuse() const;

    int getUniformLoc(const std::string &name) const;

    void setMVP(const glm::mat4 &MVP) const { setMat4("MVP", MVP); }
    void setMVP(const glm::mat3 &MVP) const { setMat3("MVP", MVP); }

    template <typename T>
    void setScalar(const std::string &name, T v) const;

    void setVec2(const std::string &name, const glm::vec2 &v) const;
    void setVec3(const std::string &name, const glm::vec3 &v) const;
    void setVec4(const std::string &name, const glm::vec4 &v) const;

    void setMat2(const std::string &name, const glm::mat2 &v) const;
    void setMat3(const std::string &name, const glm::mat3 &v) const;
    void setMat4(const std::string &name, const glm::mat4 &v) const;

    void vertexAttrib(uint32_t index, const glm::vec2 &v);
    void vertexAttrib(uint32_t index, const glm::vec3 &v);
    void vertexAttrib(uint32_t index, const glm::vec4 &v);

    void vertexAttrib(uint32_t index, int v);
    void vertexAttrib(uint32_t index, float v);
    void vertexAttrib(uint32_t index, double v);

    bool operator==(const Program &other) const { return id == other.id; }
};

using ProgramHandle = Program *;