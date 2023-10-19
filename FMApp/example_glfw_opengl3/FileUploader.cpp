#include "FileUploader.h"
#include "PlayerUploadText.h"
#include "PlayerUploadFile.h"
FileUploader::FileUploader(const bool& noMove, const bool& noResize, const bool& noCollapse, const std::string& name, const bool& visible)
    : UIPanel(noMove, noResize, noCollapse, name, visible)
{
    TextInsertPanel = std::make_shared<PlayerUploadText>();
    FileInsertPanel = std::make_shared<PlayerUploadFile>();
}

std::shared_ptr<Player> FileUploader::GetPlayerUploaded()
{
    return PlayerUploaded;
}

void FileUploader::RenderPanel()
{
    ImGui::Begin("File Uploader", nullptr, window_flags);

    ImGuiTabBarFlags tab_bar_flags = ImGuiTabBarFlags_None;
    if (ImGui::BeginTabBar("MyTabBar", tab_bar_flags))
    {
        if (ImGui::BeginTabItem("Insert File Name"))
        {
            TextInsertPanel->RenderFileUploadText(PlayerUploaded);
            FileState.AcceptingFiles = false;
            ImGui::EndTabItem();
        }
        if (ImGui::BeginTabItem("Drag and Drop File"))
        {
            FileInsertPanel->RenderFileDragAndDrop(PlayerUploaded, FileState);
            FileState.AcceptingFiles = true;
            ImGui::EndTabItem();
        }
        // to do
        if (ImGui::BeginTabItem("Paste Image"))
        {
            ImGui::Text("This is the Cucumber tab!\nblah blah blah blah blah");
            ImGui::EndTabItem();
        }
        ImGui::EndTabBar();
    }

    ImGui::End();
}

void FileUploader::SetFileState(const FileUploadState& file)
{
    FileState = file;
}

FileUploadState FileUploader::GetFileState()
{
    return FileState;
}
