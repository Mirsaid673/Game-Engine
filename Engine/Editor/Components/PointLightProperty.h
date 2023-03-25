#pragma once

#include "Imgui.h"
#include "Lighting/Lighting.h"

void InspectorDraw(PointLight& light)
{
    bool opened = ImGui::TreeNode("PointLight");
    if (!opened)
        return;

    Imgui::vec3Control("position", light.position);

    ImGui::ColorEdit3("ambient", &light.ambient.r);
    ImGui::ColorEdit3("diffuse", &light.diffuse.r);
    ImGui::ColorEdit3("specular", &light.specular.r);

    ImGui::DragFloat3("coefs", &light.coefs.x);

    ImGui::TreePop();
};