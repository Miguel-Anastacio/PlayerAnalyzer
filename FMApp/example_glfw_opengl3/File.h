#pragma once
struct FileUploadState {
    bool isDragging = false;
    char filePath[256] = ""; // Adjust the size according to your needs
    std::vector<std::string> filePaths;
    bool AcceptingFiles = false;
};
