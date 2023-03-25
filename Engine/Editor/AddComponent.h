#pragma once

#include "Imgui.h"
#include "ECS/Entity.h"

namespace Editor
{
    void addComponent(Entity& entity)
    {
        if (Imgui::centeredButton("Add component"))
            ImGui::OpenPopup("components");

        if (ImGui::BeginPopup("components"))
        {
            if (ImGui::Button("Transform"))
            {
                if (not entity.hasComponent<Transform>())
                    entity.addComponent<Transform>();
                ImGui::CloseCurrentPopup();
            }

            if (ImGui::Button("Mesh"))
            {
                if (not entity.hasComponent<Mesh>())
                    entity.addComponent<Mesh>();
                ImGui::CloseCurrentPopup();
            }

            if (ImGui::Button("PointLight"))
            {
                if (not entity.hasComponent<PointLight>())
                    entity.addComponent<PointLight>();
                ImGui::CloseCurrentPopup();
            }

            if (ImGui::Button("DirLight"))
            {
                if (not entity.hasComponent<DirLight>())
                    entity.addComponent<DirLight>();
                ImGui::CloseCurrentPopup();
            }

            ImGui::EndPopup();
        }
    }
}