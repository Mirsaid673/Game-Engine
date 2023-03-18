#include "Transform.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/euler_angles.hpp>

void Transform::translate(const glm::vec3 &v)
{
    origin += rotation[0] * v[0] +
              rotation[1] * v[1] +
              rotation[2] * v[2];
}

void Transform::setEulerAngles(const glm::vec3 &angles)
{
    rotation = glm::eulerAngleXYZ(angles.x, angles.y, angles.z);
}

glm::vec3 Transform::getEulerAngles() const
{
    glm::vec3 res;
    glm::extractEulerAngleXYZ(glm::mat4(rotation), res.x, res.y, res.z);
    return res;
}

glm::mat4 Transform::getMatrix() const
{
    glm::mat4 r;
    r[0] = glm::vec4(rotation[0], 0) * scale.x;
    r[1] = glm::vec4(rotation[1], 0) * scale.y;
    r[2] = glm::vec4(rotation[2], 0) * scale.z;
    r[3] = glm::vec4(origin, 1);

    if (parent)
        r = parent->getMatrix() * r;

    return r;
}