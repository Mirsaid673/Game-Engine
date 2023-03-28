#pragma once

#include "Shader.h"

#include "Lighting/Lighting.h"
#include "Core/Components/Material.h"
#include <string>

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

    void setMVP(const glm::mat4 &proj, const glm::mat4 &view, const glm::mat4 &model) const
    {
        setMat4("proj", proj);
        setMat4("view", view);
        setMat4("model", model);
    }
    void setMVP(const glm::mat3 &MVP) const { setMat3("MVP", MVP); }

    void setLight(const std::string &name, const PointLight &light) const
    {
        setVec3(name + ".position", light.position);
        setVec3(name + ".diffuse", light.diffuse);
        setVec3(name + ".ambient", light.ambient);
        setVec3(name + ".specular", light.specular);
        setVec3(name + ".coefs", light.coefs);
    }

    void setLight(const std::string &name, const DirLight &light) const
    {
        setVec3(name + ".direction", light.direction);
        setVec3(name + ".diffuse", light.diffuse);
        setVec3(name + ".ambient", light.ambient);
        setVec3(name + ".specular", light.specular);
    }

    void setLight(const std::string &name, const SpotLight &light) const
    {
        setVec3(name + ".position", light.position);
        setVec3(name + ".direction", light.direction);
        setVec3(name + ".diffuse", light.diffuse);
        setVec3(name + ".ambient", light.ambient);
        setVec3(name + ".specular", light.specular);
        setVec3(name + ".coefs", light.coefs);
        setFloat(name + ".cut_off", glm::cos(light.cut_off));
        setFloat(name + ".outer_cut_off", glm::cos(light.outer_cut_off));
    }

    void setMaterial(const std::string &name, const Material &material) const
    {
        setInt(name + ".diffuse_map", 0);
        setInt(name + ".specular_map", 1);

        setVec3(name + ".color", material.color);
        setFloat(name + ".shininess", material.shininess);
        setInt(name + ".maps_mask", material.texture_mask.to_ulong());

        if (material.diffuse_map)
            material.diffuse_map->use();
        if (material.specular_map)
            material.specular_map->use();
    }

    void setBool(const std::string &name, bool v) const;
    void setInt(const std::string &name, int v) const;
    void setFloat(const std::string &name, float v) const;

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