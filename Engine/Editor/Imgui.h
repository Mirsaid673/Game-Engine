#pragma once

#include "imgui/imgui.h"
#include "imgui/imgui_internal.h"
#include "imgui/imgui_stdlib.h"
#include "imgui/imgui_impl_opengl3.h"
#include "imgui/imgui_impl_glfw.h"

namespace Imgui
{
    void init(GLFWwindow *window);
    void cleanup();
    void newFrame();
    void endFrame();

    bool centeredButton(const char *label, float alignment = 0.5f);
    void vec3Control(const char *name, glm::vec3 &values, float speed = 0.1f, float reset_value = 0);
    
    void syle1();
};