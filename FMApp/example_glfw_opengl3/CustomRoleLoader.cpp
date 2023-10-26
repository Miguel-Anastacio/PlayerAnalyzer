#include "CustomRoleLoader.h"
#include "Database.h"


CustomRoleLoader::CustomRoleLoader(const bool& noMove, const bool& noResize, const bool& noCollapse, const std::string& name, const bool& visible,const Image& image)
    : ImagesPanel(noMove, noResize, noCollapse, name, visible, image)
{
    FileImage.width = FileImage.width * 0.75;
    FileImage.height = FileImage.height * 0.75;
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
                ImGui::TableSetupColumn("", ImGuiTableColumnFlags_WidthFixed, FileImage.width);
            }
            //ImGui::TableHeadersRow();
            ImGui::TableNextRow();
            ImGui::TableSetColumnIndex(0);
            for (const auto& currentPath : Paths)
            {
                if (ImGui::ImageButton(currentPath.Path.string().c_str(), (void*)(intptr_t)FileImage.FileTextureID, ImVec2(FileImage.width, FileImage.height)))
                {
                    ContentsVisibility = true;
                    fileToUse = currentPath.Path.filename().string();
                }
                for (const auto pathStrings : currentPath.FileNameStrings)
                {
                    ImGui::Text(pathStrings.c_str());
                }

                ImGui::TableNextColumn();
            }
            ImGui::EndTable();
        }
    }
    else
    {
        ImGui::Text("No custom roles files available");
    }

    if (ContentsVisibility)
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
            FileLoadedByUser = true;
        }
    }
    else if(fileToUse.size()>0)
    {
        ImGui::Spacing();
        ImGui::Spacing();
        ImGui::Spacing();
        ImGui::Spacing();
        ImGui::Spacing();
        ImGui::Text("File %s was loaded", fileToUse.c_str());
    }
    ImGui::End();

}

std::string CustomRoleLoader::GetFileToLoad()
{
    return fileToUse;
}

//bool CustomRoleLoader::LoadTexture(const char* imagePath, GLuint* out_texture, int* out_width, int* out_height)
//{
//    // Load the image using stb_image
//    int width, height, nrChannels;
//    unsigned char* data = stbi_load(imagePath, &width, &height, &nrChannels, 0);
//
//    if (data == NULL)
//        return false;
//
//    GLuint texture;
//    glGenTextures(1, &texture);
//    glBindTexture(GL_TEXTURE_2D, texture);
//
//    // Set texture parameters (optional, adjust as needed)
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
//
//    // Load image data into the OpenGL texture
//    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
//
//    // Generate mipmaps
//   // glGenerateMipmap(GL_TEXTURE_2D);
//
//    // Free image data
//    stbi_image_free(data);
//
//    *out_texture = texture;
//    *out_height = height;
//    *out_width = width;
//
//    return true;
//
//}


bool CustomRoleLoader::WasFileLoadedByUser()
{
    return FileLoadedByUser;
}
