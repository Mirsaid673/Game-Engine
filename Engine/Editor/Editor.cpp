#include "Editor.h"
#include "Imgui.h"

#include "Components/TransformProperty.h"
#include "Components/MeshProperty.h"
#include "Components/CameraProperty.h"

namespace Editor
{
    void init() { Imgui::init(window); }
    void cleanup() { Imgui::cleanup(); }
    void newFrame() { Imgui::newFrame(); }
    void endFrame() { Imgui::endFrame(); }

    Node *to_remove = nullptr;
    Node *to_rename = nullptr;
    Node *selected = nullptr;
    void drawTree()
    {
        ImGui::Begin("Nodes");
        for (auto &node : scene.nodes)
        {
            ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_FramePadding |
                                       ImGuiTreeNodeFlags_Leaf |
                                       ImGuiTreeNodeFlags_SpanAvailWidth |
                                       ImGuiTreeNodeFlags_SpanFullWidth;

            if (selected == &node)
                flags |= ImGuiTreeNodeFlags_Selected;

            bool open = ImGui::TreeNodeEx(node.name.c_str(), flags, "");

            if (ImGui::IsItemClicked(ImGuiMouseButton_Right))
                ImGui::OpenPopup("node popup");

            if (ImGui::IsItemClicked())
            {
                if (selected != &node)
                    to_rename = nullptr;
                selected = &node;
            }

            ImGui::SameLine();
            if (to_rename == &node)
            {
                ImGui::InputText("rename", &node.name);
            }
            else
                ImGui::Text("%s", node.name.c_str());

            if (ImGui::BeginPopup("node popup"))
            {
                if (ImGui::Selectable("remove"))
                {
                    to_remove = &node;
                }
                if (ImGui::Selectable("rename"))
                {
                    to_rename = &node;
                }
                ImGui::EndPopup();
            }

            if (open)
                ImGui::TreePop();
        }
        if (to_remove)
        {
            if (to_remove == selected)
                selected = nullptr;
            scene.removeNode(*to_remove);
        }

        ImGui::BeginChild(ImGuiID(1));
        ImGui::EndChild();

        if (ImGui::IsItemClicked())
            to_rename = nullptr;
        else if (ImGui::IsItemClicked(ImGuiMouseButton_Right))
            ImGui::OpenPopup("tree popup");

        if (ImGui::BeginPopup("tree popup"))
        {
            if (ImGui::Selectable("add node"))
            {
                Node& added_node = scene.addNode();
                to_rename = &added_node;
            }
            ImGui::EndPopup();
        }

        ImGui::End();
    }

    bool scene_hovered = false;
    bool sceneHovered() { return scene_hovered; }
    void drawScene(FramebufferHandle framebuffer)
    {
        ImGui::Begin("Scene", nullptr, ImGuiWindowFlags_NoDecoration);

        ImVec2 image_size = ImGui::GetContentRegionAvail();
        ImGui::Image(reinterpret_cast<ImTextureID>(framebuffer->getTexID()), image_size, {0, 1}, {1, 0});

        scene_hovered = ImGui::IsItemHovered();

        if (scene.resized)
            scene.resized = false;

        if (scene.viewport_size.x != image_size.x || scene.viewport_size.y != image_size.y)
        {
            scene.resized = true;
            scene.viewport_size = {image_size.x, image_size.y};
        }

        ImGui::End();
    }

    void drawInspector()
    {
        ImGui::Begin("Inspector");

        if (selected == nullptr)
        {
            ImGui::End();
            return;
        }

        if (auto comp = selected->tryGet<Transform>(); comp != nullptr)
            InspectorDraw(*comp, selected->getEntityID());
        if (auto comp = selected->tryGet<Mesh>(); comp != nullptr)
            InspectorDraw(*comp);
        if (auto comp = selected->tryGet<Camera>(); comp != nullptr)
            InspectorDraw(*comp);

        ImGui::End();
    }

    void drawOutput()
    {
        ImGui::Begin("Output");

        ImGui::End();
    }

    void draw(FramebufferHandle fbo)
    {
        Editor::newFrame();

        drawTree();
        drawInspector();
        drawOutput();
        drawScene(fbo);

        Editor::endFrame();
    }
};