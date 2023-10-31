#include "CustomRoleLoader.h"
#include "Database.h"

CustomRoleLoader::CustomRoleLoader(const bool& noMove, const bool& noResize, const bool& noCollapse, const std::string& name, const bool& visible,const Image& image, std::vector<Role>& role)
    : ImagesPanel(noMove, noResize, noCollapse, name, visible, image)
{
    FileImage.width = FileImage.width * 0.75;
    FileImage.height = FileImage.height * 0.75;

    Roles = &role;
}



void CustomRoleLoader::RenderPreviewFile()
{
    ImGui::BeginChild("ChildL", ImVec2(ImGui::GetContentRegionAvail().x * 0.5f, 260), false);
    ImGui::SeparatorText("File Preview");
    ImGui::TextWrapped("Roles edited by file: ");
    for (const auto& rolesEdited : FilePreview)
    {
        ImGui::TextWrapped(rolesEdited.c_str());
    }
    ImGui::EndChild();
}

void CustomRoleLoader::CreatePreview(const std::string& fileName)
{
    if (fileName != FileHovered)
        FilePreview = ReadRolesEditedByFile(fileName, *Roles);
}

void CustomRoleLoader::RenderPanel()
{
    ImGui::Begin(Name.c_str(), nullptr, window_flags);
    FileLoadedByUser = false;
    int columns = 0;
    if (Paths.size() > 14)
    {
        columns = 14;
    }
    else
    {
        columns = Paths.size();
    }

    if (columns > 0)
    {
        if (ImGui::BeginTable("tablefiles", columns))
        {
            for (int i = 0; i < columns; i++)
            {
                ImGui::TableSetupColumn("", ImGuiTableColumnFlags_WidthFixed, FileImage.width + 10);
            }
            //ImGui::TableHeadersRow();
            ImGui::TableNextRow();
            ImGui::TableSetColumnIndex(0);
            for (auto& currentPath : Paths)
            {
                if (ImGui::ImageButton(currentPath.Path.string().c_str(), (void*)(intptr_t)FileImage.FileTextureID, ImVec2(FileImage.width, FileImage.height)))
                {
                    fileToUse = currentPath.Path.filename().string();
                    FileLoadedByUser = true;
                }
                ImGui::SetItemTooltip("Press to load file");

                if (ImGui::IsItemHovered())
                {   
                    currentPath.Hovered = true;
                    CreatePreview(currentPath.Path.string());
                    FileHovered = currentPath.Path.string();
                }
                else 
                {
                    currentPath.Hovered = false;
                    PreviewVisible = false;
                    FileHovered = "";
                    //FilePreview.clear();
                }

                for (const auto pathStrings : currentPath.FileNameStrings)
                {
                    ImGui::Text(pathStrings.c_str());
                }

                ImGui::TableNextColumn();
            }

            // see if any button is hovered
            for (const auto& path : Paths)
            {
                if (path.Hovered)
                    PreviewVisible = true;
            }
              

            ImGui::EndTable();
        }
    }
    else
    {
        ImGui::Text("No custom roles files available");
    }

   /* if (ContentsVisibility)
    {
        ImGui::Spacing();
        ImGui::Spacing();
        ImGui::Spacing();
        ImGui::Spacing();
        ImGui::Spacing();
        ImGui::Text("File Selected: %-25s", fileToUse.c_str());
        ImGui::Spacing();
        ImGui::Spacing();
        if (ImGui::Button("Load File"))
        {
            ImGui::SameLine(100.0f, 200.0f);
            ContentsVisibility = false;
        }
    }*/
    if(fileToUse.size()>0)
    {
        ImGui::Spacing();
        ImGui::Spacing();
        ImGui::Spacing();
        ImGui::Spacing();
        ImGui::Spacing();
        ImGui::Text("File %s was loaded", fileToUse.c_str());
    }

    if (PreviewVisible)
        RenderPreviewFile();
    else
        FilePreview.clear();

    ImGui::End();

}

std::string CustomRoleLoader::GetFileToLoad()
{
    return fileToUse;
}



bool CustomRoleLoader::WasFileLoadedByUser()
{
    return FileLoadedByUser;
}
