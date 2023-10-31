#pragma once
#include "ImagesPanel.h"
#include <filesystem>
#include <iostream>
#include "stb_image.h"
#include "TextureManager.h"


struct Role;
class CustomRoleLoader : public ImagesPanel
{

public:
    CustomRoleLoader(const bool& noMove, const bool& noResize, const bool& noCollapse, const std::string& name, const bool& visible, const Image& image, std::vector<Role>&role);
    void RenderPanel() override;

    void RenderPreviewFile();
    void CreatePreview(const std::string& fileName);


    std::string GetFileToLoad();
    bool WasFileLoadedByUser();

private:
    std::string fileToUse;
    std::vector<Role>* Roles;
    bool FileLoadedByUser = false;

    std::vector<std::string> FilePreview;
    bool PreviewVisible = false;
    std::string FileHovered;
   // bool LoadTexture(const char* imagePath, GLuint* out_texture, int* out_width, int* out_height);
};

