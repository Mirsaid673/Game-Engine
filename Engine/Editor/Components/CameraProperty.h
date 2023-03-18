#pragma once

#include "Imgui.h"
#include "Camera.h"

void InspectorDraw(Camera &camera)
{
    bool opened = ImGui::TreeNode("Camera");
    if (!opened)
        return;

    const char const *items[Camera::Type::MAX] =
        {
            "ortho",
            "perspective",
        };
    ImGui::Text("projection");
    if (ImGui::Combo(" ", (int *)&camera.type, items, Camera::Type::MAX))
        camera.recalcProj();

    if (camera.type == Camera::Type::ORTHO)
    {
        ImGui::Columns(2);

        ImGui::DragFloat("left", &camera.left);
        ImGui::DragFloat("bottom", &camera.bottom);
        ImGui::DragFloat("near", &camera.near);

        ImGui::NextColumn();

        ImGui::DragFloat("right", &camera.right);
        ImGui::DragFloat("top", &camera.top);
        ImGui::DragFloat("far", &camera.far);
    }
    else
    {
        ImGui::DragFloat("fov", &camera.fov);
        ImGui::DragFloat("aspect", &camera.aspect);
    }

    ImGui::TreePop();
}