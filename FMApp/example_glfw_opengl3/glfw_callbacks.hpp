#include <GLFW/glfw3.h>
#include <string.h>
#include "File.h"

namespace Callback {

    FileUploadState fileUploadState;

    // callback function for dragging a dropping a file
    // Example using GLFW
    void DragAndDropCallback(GLFWwindow* window, int count, const char** paths) {
        if (count > 0) {
            // Assuming you want to use only the first file dragged
            if (fileUploadState.AcceptingFiles)
            {
                fileUploadState.isDragging = true;
                strncpy(fileUploadState.filePath, paths[0], sizeof(fileUploadState.filePath) - 1);
                fileUploadState.filePath[sizeof(fileUploadState.filePath) - 1] = '\0';
            }
        }
    }
}
