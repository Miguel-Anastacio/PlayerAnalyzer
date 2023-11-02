#include <GLFW/glfw3.h>
#include <string.h>
#include "File.h"

namespace Callback {

    FileUploadState fileUploadState;

    // callback function for dragging a dropping a file
    // Example using GLFW
    void DragAndDropCallback(GLFWwindow* window, int count, const char** paths) {
        fileUploadState.filePaths.clear();
        fileUploadState.isDragging = true;
        for(int i = 0; i < count; i++)
        {
            if (fileUploadState.AcceptingFiles)
            {
                std::string currentPath = paths[i];
                strncpy(fileUploadState.filePath, paths[i], sizeof(fileUploadState.filePath) - 1);
                fileUploadState.filePath[sizeof(fileUploadState.filePath) - 1] = '\0';

                fileUploadState.filePaths.emplace_back(currentPath);
            }
        }
    }
}
