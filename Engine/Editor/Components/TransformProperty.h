#pragma once

#include "Imgui.h"
#include "Transform.h"
#include <unordered_map>

std::unordered_map<EntityID, glm::vec3> euler_angles;

void InspectorDraw(Transform& transform, EntityID id)
{
    bool opened = ImGui::TreeNode("Transform");
    if (!opened)
        return;

    Imgui::vec3Control("position", transform.origin);

    glm::vec3& rotation = euler_angles[id];
    Imgui::vec3Control("rotation", rotation, 1.0f);
    transform.setEulerAngles(glm::radians(rotation));
    rotation = glm::mod(rotation + glm::vec3(360), glm::vec3(720)) - glm::vec3(360);
    
    Imgui::vec3Control("scale", transform.scale, 0.1, 1);

    ImGui::TreePop();
};