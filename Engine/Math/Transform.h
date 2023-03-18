#pragma once

#include "Basis.h"

class Transform
{
public:
    Basis rotation;
    glm::vec3 origin;
    glm::vec3 scale;
    Transform *parent = nullptr;

    Transform() : origin(0.0f), scale(1.0f) {}

    void translate(const glm::vec3 &v);

    void rotate(float angle, const glm::vec3 &axis) { rotation.rotate(angle, axis); }
    void rotateX(float angle) { rotation.rotateX(angle); }
    void rotateY(float angle) { rotation.rotateY(angle); }
    void rotateZ(float angle) { rotation.rotateZ(angle); }
    
    void setEulerAngles(const glm::vec3& angles);
    glm::vec3 getEulerAngles() const;

    glm::mat4 getMatrix() const;

    glm::mat4 operator*(const glm::mat4 &m) { return getMatrix() * m; }
    glm::mat4 operator*(const Transform &t) { return getMatrix() * t.getMatrix(); }
};