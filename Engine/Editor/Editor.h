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

    void brawserInit();
    void brawserCleanup();

    void drawTree();
    void drawScene(FramebufferHandle framebuffer);
    void drawInspector();
    void drawOutput();
    void drawBrowser();

    void draw(FramebufferHandle fbo);

    bool sceneHovered();
};