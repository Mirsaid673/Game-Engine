#include "Program.h"

#include <fstream>
#include <sstream>

#include "Resource.h"
#include "Log.h"

Program::Program(const ShaderHandle vert, const ShaderHandle frag)
{
    create(vert, frag);
}

Program::Program(const std::string &vs_file, const std::string &fs_file)
{
    create(vs_file, fs_file);
}

void Program::create()
{
    id = glCreateProgram();
}

void Program::create(const ShaderHandle vert, const ShaderHandle frag)
{
    create();
    attachShader(vert);
    attachShader(frag);
    link();
}

void Program::create(const std::string &vs_file, const std::string &fs_file)
{
    Shader vert(Resource::readFile(vs_file).c_str(), Shader::Type::VERTEX);
    Shader frag(Resource::readFile(fs_file).c_str(), Shader::Type::FRAGMENT);

    create(&vert, &frag);

    vert.destroy();
    frag.destroy();
}

void Program::destroy()
{
    glDeleteProgram(id);
    id = -1;
}

void Program::attachShader(const ShaderHandle shader) const
{
    glAttachShader(id, shader->id);
}

void Program::link() const
{
    glLinkProgram(id);
    linkInfo();
}

void Program::use() const
{
    glUseProgram(id);
}

void Program::unuse() const
{
    glUseProgram(0);
}

void Program::linkInfo() const
{
    constexpr int logSize = 512;
    GLint success;
    GLchar infoLog[logSize];
    glGetProgramiv(id, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(id, logSize, nullptr, infoLog);
        Log::error("ERROR::PROGRAM::LINK_FAILED\n{}", infoLog);
    }
}

int Program::getUniformLoc(const std::string &name) const
{
    return glGetUniformLocation(id, name.c_str());
}

template <>
void Program::setScalar<int>(const std::string &name, int v) const
{
    glUniform1i(getUniformLoc(name), v);
}

template <>
void Program::setScalar<uint32_t>(const std::string &name, uint32_t v) const
{
    glUniform1ui(getUniformLoc(name), v);
}

template <>
void Program::setScalar<float>(const std::string &name, float v) const
{
    glUniform1f(getUniformLoc(name), v);
}

template <>
void Program::setScalar<double>(const std::string &name, double v) const
{
    glUniform1d(getUniformLoc(name), v);
}

void Program::setVec2(const std::string &name, const glm::vec2 &v) const
{
    glUniform2fv(getUniformLoc(name), 1, &v.x);
}

void Program::setVec3(const std::string &name, const glm::vec3 &v) const
{
    glUniform3fv(getUniformLoc(name), 1, &v.x);
}

void Program::setVec4(const std::string &name, const glm::vec4 &v) const
{
    glUniform4fv(getUniformLoc(name), 1, &v.x);
}

void Program::setMat2(const std::string &name, const glm::mat2 &v) const
{
    glUniformMatrix2fv(getUniformLoc(name), 1, GL_FALSE, &v[0][0]);
}

void Program::setMat3(const std::string &name, const glm::mat3 &v) const
{
    glUniformMatrix3fv(getUniformLoc(name), 1, GL_FALSE, &v[0][0]);
}

void Program::setMat4(const std::string &name, const glm::mat4 &v) const
{
    glUniformMatrix4fv(getUniformLoc(name), 1, GL_FALSE, &v[0][0]);
}

void Program::vertexAttrib(uint32_t index, const glm::vec2 &v)
{
    glVertexAttrib2fv(index, &v.x);
}

void Program::vertexAttrib(uint32_t index, const glm::vec3 &v)
{
    glVertexAttrib3fv(index, &v.x);
}
void Program::vertexAttrib(uint32_t index, const glm::vec4 &v)
{
    glVertexAttrib4fv(index, &v.x);
}

void Program::vertexAttrib(uint32_t index, int v)
{
    glVertexAttribI1i(index, v);
}
void Program::vertexAttrib(uint32_t index, float v)
{
    glVertexAttrib1f(index, v);
}
void Program::vertexAttrib(uint32_t index, double v)
{
    glVertexAttrib1d(index, v);
}
