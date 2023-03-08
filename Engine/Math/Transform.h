#pragma once

#include "Basis.h"

class Transform
{
public:
    Basis basis;
    glm::vec3 origin;

    Transform() : origin(0.0f) {}

    void translate(const glm::vec3 &v);

    void rotate(float angle, const glm::vec3 &axis) { basis.rotate(angle, axis); }
    void rotateX(float angle) { basis.rotateX(angle); }
    void rotateY(float angle) { basis.rotateY(angle); }
    void rotateZ(float angle) { basis.rotateZ(angle); }

    glm::mat4 getMatrix() const;

    glm::mat4 operator*(const glm::mat4 &m) { return getMatrix() * m; }
    glm::mat4 operator*(const Transform &t) { return getMatrix() * t.getMatrix(); }
};