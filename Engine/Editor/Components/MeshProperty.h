#pragma once

#include "Imgui.h"
#include "Mesh.h"

void InspectorDraw(Mesh& transform)
{
    bool opened = ImGui::TreeNode("Mesh");
    if (!opened)
        return;
    ImGui::Text("mesh -_-");

    ImGui::TreePop();
}