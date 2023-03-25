#pragma once

#include <glm/glm.hpp>

class BaseLight
{
public:
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
};

class DirLight : public BaseLight
{
public:
    glm::vec3 direction;
};

class PointLight : public BaseLight
{
public:
    glm::vec3 position;
    glm::vec3 coefs = glm::vec3(1, 0, 0);
};

class SpotLight : BaseLight
{
public:
    glm::vec3 position;
    glm::vec3 direction;
    glm::vec3 coefs = glm::vec3(1, 0, 0);
};