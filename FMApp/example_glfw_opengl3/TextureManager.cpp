#include "TextureManager.h"

TextureManager::TextureManager()
{
    if (LoadTextureFromFile("textures/file_icon.png", &FileImage) == false)
    {
        std::cout << "Error loading texture textures/file_icon.png\n" << std::endl;
    }
    if (LoadTextureFromFile("textures/player.png", &PlayerImage) == false)
    {
        std::cout << "Error loading texture textures/player.png\n" << std::endl;
    }
}


TextureManager::~TextureManager()
{
    if (FileImage.FileTextureID != 0)
    {
        glDeleteTextures(1, &FileImage.FileTextureID);
    }
    if (PlayerImage.FileTextureID != 0)
    {
        glDeleteTextures(1, &PlayerImage.FileTextureID);
    }
}

bool TextureManager::LoadTextureFromFile(const char* imagePath, Image* image)
{
    // Load the image using stb_image
    int width, height, nrChannels;
    unsigned char* data = stbi_load(imagePath, &width, &height, &nrChannels, 0);

    if (data == NULL)
        return false;

    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    // Set texture parameters (optional, adjust as needed)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    // Load image data into the OpenGL texture
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

    // Generate mipmaps
    //glGenerateMipmap(GL_TEXTURE_2D);

    // Free image data
    stbi_image_free(data);

    image->FileTextureID = texture;
    image->height = height;
    image->width = width;

    return true;
}

const Image& TextureManager::GetFileImage()
{
    return FileImage;
}

const Image& TextureManager::GetPlayerImage()
{
    return PlayerImage;
}
