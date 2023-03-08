#include "Shader.h"
#include "Log.h"

GLenum GLtranslate(Shader::Type t);

Shader::Shader(const char *code, Type type)
{
    create(code, type);
}

void Shader::create(const char *code, Type type)
{
    id = glCreateShader(GLtranslate(type));
    glShaderSource(id, 1, &code, nullptr);
    glCompileShader(id);

    compileInfo();
}

void Shader::destroy()
{
    glDeleteShader(id);
    id = -1;
}

void Shader::compileInfo()
{
    constexpr int logSize = 512;
    GLint success;
    GLchar infoLog[logSize];
    glGetShaderiv(id, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(id, logSize, NULL, infoLog);
        Log::error("ERROR::SHADER::COMPILATION_FAILED\n{}", infoLog);
    }
}

GLenum GLtranslate(Shader::Type t)
{
    static const GLenum tr[] =
        {
            GL_VERTEX_SHADER,
            GL_FRAGMENT_SHADER,
        };
    return tr[t];
}