#pragma once
#include<glew.h>
#include <GLFW/glfw3.h>
#include "stb_image.h"
#include <iostream>
struct Image
{
    GLuint FileTextureID;
    int width = 0;
    int height = 0;
};
class TextureManager
{
    Image FileImage;
    Image PlayerImage;

public:
    TextureManager();
    ~TextureManager();
    bool LoadTextureFromFile(const char* imagePath, Image* image);
    const Image& GetFileImage();
    const Image& GetPlayerImage();
};

