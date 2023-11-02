#include <GLFW/glfw3.h>
#include <string.h>
#include "File.h"

namespace Callback {

    FileUploadState fileUploadState;

    // callback function for dragging a dropping a file
    // Example using GLFW
    void DragAndDropCallback(GLFWwindow* window, int count, const char** paths) {
        fileUploadState.filePaths.clear();
        for(int i = 0; i < count; i++)
        {
            if (fileUploadState.AcceptingFiles)
            {
                char currentPath[256];
                fileUploadState.isDragging = true;
                strncpy(currentPath, paths[0], sizeof(currentPath) - 1);
                currentPath[sizeof(fileUploadState.filePath) - 1] = '\0';

                fileUploadState.filePaths.emplace_back(currentPath);
            }
        }
    }
}
