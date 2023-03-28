#include "Editor.h"
#include "Imgui.h"
#include "Textures/Texture.h"

#include <filesystem>

namespace Editor
{
    void toParent();

    std::filesystem::path current_dir = std::filesystem::current_path();
    Texture dir_icon;
    Texture file_icon;

    float size = 64.0f;
    float padding = 16.0f;
    void brawserInit()
    {
        dir_icon.create(Resource::loadImage("DirectoryIcon.png"));
        file_icon.create(Resource::loadImage("FileIcon.png"));
    }

    void brawserCleanup()
    {
        dir_icon.destroy();
        file_icon.destroy();
    }

    void drawBrowser()
    {
        ImGui::Begin("Content Browser");

        ImGui::Text(current_dir.c_str());

        float cellSize = size + padding;

        float panelWidth = ImGui::GetContentRegionAvail().x;
        int columnCount = (int)(panelWidth / cellSize);
        columnCount = std::max(1, columnCount);

        ImGui::Columns(columnCount, 0, false);
        toParent();
        for (auto &entry_dir : std::filesystem::directory_iterator(current_dir))
        {
            bool is_directory = std::filesystem::is_directory(entry_dir);
            std::string name = entry_dir.path().filename().string();

            ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 0, 0));

            ImTextureID texture = reinterpret_cast<ImTextureID>(dir_icon.getID());
            if (not is_directory)
                texture = reinterpret_cast<ImTextureID>(file_icon.getID());

            ImGui::ImageButton(texture, {size, size}, {0, 1}, {1, 0});
            ImGui::PopStyleColor();

            if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
            {
                if (is_directory)
                    current_dir /= entry_dir.path().filename();
            }

            ImGui::Text(name.c_str());
            ImGui::NextColumn();
        }

        ImGui::Columns(1);

        ImGui::SliderFloat("Thumbnail Size", &size, 16, 512);
        ImGui::SliderFloat("Padding", &padding, 0, 32);

        ImGui::End();
    }

    void toParent()
    {
        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 0, 0));

        ImTextureID texture = reinterpret_cast<ImTextureID>(dir_icon.getID());
        ImGui::ImageButton(texture, {size, size}, {0, 1}, {1, 0});

        ImGui::PopStyleColor();

        if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
        {
            current_dir = current_dir.parent_path();
        }

        ImGui::Text("..");
        ImGui::NextColumn();
    }

}