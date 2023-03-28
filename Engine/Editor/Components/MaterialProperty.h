#pragma once

#include "Imgui.h"
#include "Components/Material.h"

void InspectorDraw(Material& material)
{
    bool opened = ImGui::TreeNode("Material");
    if (!opened)
        return;
    ImGui::DragFloat("shininess", &material.shininess, 0.05, 0.0f, 128.0f);

    bool diff = material.texture_mask[0];
    bool spec = material.texture_mask[1];
    ImGui::Checkbox("difuse map", &diff);
    ImGui::Checkbox("specular map", &spec);
    material.texture_mask.set(0, diff);
    material.texture_mask.set(1, spec);

    ImGui::TreePop();
}