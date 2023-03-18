#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>

void Camera::recalcProj()
{
    if (type == ORTHO)
        ortho(left, right, bottom, top, near, far);
    else
        perspective(fov, aspect, near, far);
}

void Camera::perspective(float angle, float asp, float n, float f)
{
    type = Type::PERSPECTIVE;

    fov = angle;
    aspect = asp;
    near = n;
    far = f;
    setWidth(getHeight() * aspect);

    proj = glm::perspectiveLH(fov, aspect, near, far);
}

void Camera::ortho(float l, float r, float b, float t, float n, float f)
{
    type = Type::ORTHO;

    left = l;
    right = r;
    bottom = b;
    top = t;
    near = n;
    far = f;

    proj = glm::orthoLH(left, right, bottom, top, near, far);
}