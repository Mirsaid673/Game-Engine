#pragma once

#include <vector>
#include <glm/glm.hpp>
#include "Core.h"
#include "Material.h"

struct Mesh
{
    std::vector<glm::vec3> positions;
    std::vector<glm::vec3> normals;
    std::vector<glm::vec3> colors;
    std::vector<glm::vec2> tex_coords0;
    std::vector<glm::vec2> tex_coords1;

    std::vector<u32> indices;

    std::string texture_path;
};