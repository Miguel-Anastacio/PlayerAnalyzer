#pragma once
#include "ImagesPanel.h"
#include <filesystem>
#include <iostream>
#include "stb_image.h"
#include "TextureManager.h"



class CustomRoleLoader : public ImagesPanel
{
    std::string fileToUse;
    bool FileLoadedByUser = false;

public:
    CustomRoleLoader(const bool& noMove, const bool& noResize, const bool& noCollapse, const std::string& name, const bool& visible, const Image& image);
    void RenderPanel() override;

    std::string GetFileToLoad();
    bool WasFileLoadedByUser();

   // bool LoadTexture(const char* imagePath, GLuint* out_texture, int* out_width, int* out_height);
};

