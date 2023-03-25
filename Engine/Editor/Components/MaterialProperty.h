#pragma once

#include "Imgui.h"
#include "Components/Material.h"

void InspectorDraw(Material& material)
{
    bool opened = ImGui::TreeNode("Material");
    if (!opened)
        return;
    ImGui::DragFloat("shininess", &material.shininess, 0.05, 0.0f, 128.0f);

    ImGui::TreePop();
}