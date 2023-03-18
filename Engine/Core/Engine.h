#pragma once

#include "Context.h"
#include "Renderer/Renderer.h"

namespace Engine
{
    struct InitInfo
    {
        std::string title = "Engine";
        u32 width = 800;
        u32 height = 600;
        glm::vec3 clear_color = glm::vec3(0.8, 0.78, 0.5);
    };

    bool init(const InitInfo &init_info);
    bool cleanup();
}

#include "Engine.inl"