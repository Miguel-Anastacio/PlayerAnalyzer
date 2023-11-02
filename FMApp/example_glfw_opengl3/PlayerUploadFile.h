#pragma once
#include "UIPanel.h"
#include "File.h"
#include <memory>
class Player;

class PlayerUploadFile : public UIPanel
{
public:
    // returns a bool when a valid file is dragged to file uploader
    std::vector<Player> RenderFileDragAndDrop(std::shared_ptr<Player>& player, FileUploadState& file);
protected:
    bool ValidFile = true;
   
};

