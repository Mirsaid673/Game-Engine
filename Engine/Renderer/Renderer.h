#pragma once

#include <glm/glm.hpp>
#include "GPU.h"

namespace Renderer
{
    void enableDebug();

    void init();

    void enableDepthTest();
    void clearColor(const glm::vec3 &color);
    void clearColor(u32 color);
    void clearBuffers();

    void setViewport(const glm::uvec2 &size);
    void setViewport(const glm::uvec2 &origin, const glm::uvec2 &size);

    void drawVertexArray(VertexArrayHandle vao);
}