#pragma once

#include "Imgui.h"
#include "Lighting/Lighting.h"

void InspectorDraw(SpotLight &light)
{
    bool opened = ImGui::TreeNode("SpotLight");
    if (!opened)
        return;

    Imgui::vec3Control("position", light.position);
    Imgui::vec3Control("direction", light.direction);
    glm::vec2 deg = {glm::degrees(light.cut_off), glm::degrees(light.outer_cut_off)};
    ImGui::DragFloat("inner cut off", &deg.x, 1.0f, 0.0f, deg.y);
    ImGui::DragFloat("outer cut off", &deg.y, 1.0f, deg.x, 180.0f);
    light.cut_off = glm::radians(deg.x);
    light.outer_cut_off = glm::radians(deg.y);

    ImGui::ColorEdit3("ambient", &light.ambient.r);
    ImGui::ColorEdit3("diffuse", &light.diffuse.r);
    ImGui::ColorEdit3("specular", &light.specular.r);

    ImGui::DragFloat3("coefs", &light.coefs.x);

    ImGui::TreePop();
};