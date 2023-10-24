#pragma once
#include "UIPanel.h"
#include <filesystem>
#include <iostream>
class CustomRoleLoader : public UIPanel
{
    std::vector<std::filesystem::path> Paths;
    std::string fileToUse;
public:
    CustomRoleLoader(const bool& noMove, const bool& noResize, const bool& noCollapse, const std::string& name, const bool& visible);

    void RenderPanel() override;

    std::vector<std::filesystem::path> GetFilesInDirectory(const char* Directory);
    void ClearFiles();
    std::string GetFileToLoad();
};

