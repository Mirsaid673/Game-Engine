#pragma once

#include "Imgui.h"
#include "Lighting/Lighting.h"

void InspectorDraw(DirLight& light)
{
    bool opened = ImGui::TreeNode("DirLight");
    if (!opened)
        return;

    Imgui::vec3Control("direction", light.direction);

    ImGui::ColorEdit3("ambient", &light.ambient.r);
    ImGui::ColorEdit3("diffuse", &light.diffuse.r);
    ImGui::ColorEdit3("specular", &light.specular.r);

    ImGui::TreePop();
};