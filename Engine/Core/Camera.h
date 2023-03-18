#pragma once

#include "Transform.h"

class Camera
{
public:
    enum Type
    {
        ORTHO,
        PERSPECTIVE,
        MAX,
    };

private:
    glm::mat4 proj;

public:
    Transform transform;
    float left;
    float right;
    float bottom;
    float top;
    float near;
    float far;
    float aspect;
    float fov;
    Type type;

    Camera() : proj(1.0f), left(-1.0f), right(1.0f),
               bottom(-1.0f), top(1.0f),
               near(0.0f), far(1.0f),
               fov(0.0f), type(ORTHO) {}

    void recalcProj();
    void perspective(float angle, float aspect, float near = 0, float far = 100);
    void ortho(float left, float rigth, float bottom, float top, float near, float far);

    glm::mat4 getProjection() const { return proj; }
    glm::mat4 getView() const { return glm::inverse(transform.getMatrix()); }
    glm::mat4 getVP() const { return getProjection() * getView(); }

    float getWidth() const { return right - left; }
    float getHeight() const { return top - bottom; }

    void setWidth(float w) { right = w / 2.0f; left = -right; }
    void setHeight(float h) { top = h / 2.0f; bottom = -top; }

    glm::mat4 operator*(const Transform &tr) { return getVP() * tr.getMatrix(); }
};