#pragma once

#include "Transform.h"

class Camera
{
private:
    glm::mat4 proj;

public:
    Transform transform;

    Camera() : proj(1.0f) {}

    void perspective(float angle, float aspect, float near = 0, float far = 100);
    void ortho();

    glm::mat4 getProjection() const { return proj; }
    glm::mat4 getView() const { return glm::inverse(transform.getMatrix()); }
    glm::mat4 getPV() const { return getProjection() * getView(); }

    glm::mat4 operator*(const Transform &tr) { return getPV() * tr.getMatrix(); }
};