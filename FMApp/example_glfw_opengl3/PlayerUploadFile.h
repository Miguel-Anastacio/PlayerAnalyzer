#pragma once
#include "UIPanel.h"
#include "File.h"
#include <memory>
class Player;

class PlayerUploadFile : public UIPanel
{
public:
    void RenderFileDragAndDrop(std::shared_ptr<Player>& player, FileUploadState& file);
protected:
    bool ValidFile = true;
};

