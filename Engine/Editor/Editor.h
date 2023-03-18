#pragma once

#include "Context.h"
#include "Log.h"

#include <unordered_map>
#include <glm/glm.hpp>

namespace Editor
{
    void init();
    void cleanup();
    void newFrame();
    void endFrame();

    void drawTree();
    void drawScene(FramebufferHandle framebuffer);
    void drawInspector();
    void drawOutput();

    void draw(FramebufferHandle fbo);

    bool sceneHovered();
};