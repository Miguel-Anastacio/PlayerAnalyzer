#pragma once
struct FileUploadState {
    bool isDragging = false;
    char filePath[256] = ""; // Adjust the size according to your needs
    std::vector<char [256]> filePaths;
    bool AcceptingFiles = false;
};
