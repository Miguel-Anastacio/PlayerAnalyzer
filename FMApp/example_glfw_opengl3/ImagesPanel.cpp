#include "ImagesPanel.h"

ImagesPanel::ImagesPanel(const bool& noMove, const bool& noResize, const bool& noCollapse, const std::string& name, const bool& visible, const Image& image)
    : UIPanel(noMove, noResize, noCollapse, name, visible)
{
    FileImage = image;
}

void ImagesPanel::LoadFilesInDirectory(const char* Directory)
{
    // look for files in the directory
    // Create a directory iterator for the specified directory path.
    // Convert the input directory to a std::filesystem::path.
    std::filesystem::path directoryPath(Directory);

    // Check if the directory exists.
    if (std::filesystem::exists(directoryPath) && std::filesystem::is_directory(directoryPath))
    {
        std::filesystem::directory_iterator directoryIterator(directoryPath);
        for (const auto& entry : directoryIterator)
        {
            if (entry.is_regular_file())
            {
                // split file name 
                ImVec2 text = ImGui::CalcTextSize(entry.path().filename().string().c_str());
                std::vector<std::string> fileStrings;
                // if file name is too big
                if (text.x > FileImage.width)
                {
                    std::string toEvaluate = entry.path().filename().filename().string();
                    int slices = 1;
                    int exp = 0;
                    // split file name until it fits
                    while (ImGui::CalcTextSize(toEvaluate.c_str()).x > FileImage.width)
                    {
                        toEvaluate = toEvaluate.substr(0, toEvaluate.size() / 2);
                        exp++;
                        slices = pow(2, exp);
                    }

                    for (int i = 0; i < slices; i++)
                    {
                        fileStrings.emplace_back(entry.path().filename().string().substr(i * toEvaluate.size(), entry.path().filename().string().size() / slices));
                    }
                }
                else
                {
                    fileStrings.emplace_back(entry.path().filename().filename().string());
                }
                Paths.emplace_back(entry.path(), fileStrings);
            }
        }
    }
}

void ImagesPanel::ClearFiles()
{
    Paths.clear();
}
