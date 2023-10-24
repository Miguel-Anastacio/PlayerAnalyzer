#include "CustomRoleLoader.h"

#include "Database.h"
CustomRoleLoader::CustomRoleLoader(const bool& noMove, const bool& noResize, const bool& noCollapse, const std::string& name, const bool& visible)
    : UIPanel(noMove, noResize, noCollapse, name, visible)
{

}

void CustomRoleLoader::RenderPanel()
{
    ImGui::Begin(Name.c_str(), nullptr, window_flags);
    for (const auto& path : Paths)
    {
        if (ImGui::Button(path.filename().string().c_str()))
        {
            fileToUse = path.filename().string();
        }
        
    }
    ImGui::End();

}

std::vector<std::filesystem::path> CustomRoleLoader::GetFilesInDirectory(const char* Directory)
{
    // look for files in the directory
    std::string directoryPath = Directory;
    // Create a directory iterator for the specified directory path.
    std::filesystem::directory_iterator directoryIterator(directoryPath);
    for (const auto& entry : directoryIterator)
    {
        if (entry.is_regular_file())
        {
            // Display the file path
            std::cout << entry.path() << std::endl;
            Paths.emplace_back(entry.path());

        }
    }

    return Paths;
}

std::string CustomRoleLoader::GetFileToLoad()
{
    return fileToUse;
}

void CustomRoleLoader::ClearFiles()
{
    Paths.clear();
}
