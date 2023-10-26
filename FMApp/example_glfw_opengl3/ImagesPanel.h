#pragma once
#include "UIPanel.h"
#include <filesystem>
#include "TextureManager.h"
// structure used to render file names
// it saves the file name into separate strings
//so that we can wrap the text
struct File
{
    std::filesystem::path Path;
    std::vector<std::string> FileNameStrings;

    File(std::filesystem::path path, const std::vector<std::string>& fileStrings)
        : Path(path), FileNameStrings(fileStrings)
    {

    };
};
class ImagesPanel :  public UIPanel
{
protected:
    std::vector<File> Paths;
    std::string FileToUse;

    Image FileImage;

public:
    ImagesPanel(const bool& noMove, const bool& noResize, const bool& noCollapse, const std::string& name, const bool& visible, const Image& image);
    
    //void RenderPanel() override;

    void LoadFilesInDirectory(const char* Directory);
    void ClearFiles();

};

