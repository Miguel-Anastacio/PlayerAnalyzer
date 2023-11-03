#include "SaveRolePanel.h"
#include "Database.h"
SaveRolePanel::SaveRolePanel(const bool& noMove, const bool& noResize, const bool& noCollapse, const std::string& name, const bool& visible, const Image& image)
    : ImagesPanel(noMove, noResize, noCollapse, name, visible, image)
{
    FileImage.width = FileImage.width * 0.5;
    FileImage.height = FileImage.height * 0.5;
}

void SaveRolePanel::RenderPanel()
{
    ImGui::Begin(Name.c_str(), nullptr, window_flags);

    ImGuiTabBarFlags tab_bar_flags = ImGuiTabBarFlags_None;
    if (ContentsVisibility)
    {
        if (ImGui::BeginTabBar("MyTabBar", tab_bar_flags))
        {
            if (ImGui::BeginTabItem("Enter File Name"))
            {
                FeedbackVisibleTab2 = false;
                const int bufferSize = 30;
                char inputBuffer[bufferSize] = "";
                // display save file window
                ImGui::Text("Save Role Window");

                // ImGui InputText widget
                bool status = ImGui::InputText("Enter File Name", inputBuffer, bufferSize, ImGuiInputTextFlags_EnterReturnsTrue);
                ImGui::SetItemTooltip("File Name can not be larger than 30");
                if (status)
                {
                    FeedbackVisibleTab1 = WriteRoleWeightsFile(*RoleToSave, inputBuffer);
                    //memset(inputBuffer, 0, bufferSize);
                    FileNameSaved = inputBuffer;
                    if (FeedbackVisibleTab1)
                    {
                        ClearFiles();
                        LoadFilesInDirectory("custom_roles");
                    }

                }
                RenderFeedback(FileNameSaved, FeedbackVisibleTab1);

                ImGui::EndTabItem();
            }

            if (ImGui::BeginTabItem("Add to Existing file"))
            {
                FeedbackVisibleTab1 = false;
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
                                FileToUse = currentPath.Path.filename().string();
                            }
                            for (const auto pathStrings : currentPath.FileNameStrings)
                            {
                                ImGui::Text(pathStrings.c_str());
                            }

                            ImGui::TableNextColumn();
                        }
                        ImGui::EndTable();

                        if (FileToUse.size() > 0)
                        {
                            std::string string = "Add Role Weight to custom file: " + FileToUse;
                            if (ImGui::Button(string.c_str()))
                            {
                                WriteRoleWeightsFile(*RoleToSave, FileToUse);
                                FeedbackVisibleTab2 = true;
                                FileNameSaved = FileToUse;
                                FileToUse.clear();
                            }
                        }

                        RenderFeedback(FileNameSaved, FeedbackVisibleTab2);

                    }
                }
                else
                {
                    ImGui::Text("No custom roles available");
                }
                ImGui::EndTabItem();
            }

            ImGui::EndTabBar();
        }
    }
    ImGui::End();
}

void SaveRolePanel::RenderFeedback(const std::string& text, const bool& visibility)
{
    if (visibility)
    {
        ImGui::Text("Role weights saved to file: %s", text.c_str());
    }
}

void SaveRolePanel::SetRoleToSave(const Role* role)
{
    RoleToSave = role;
}
