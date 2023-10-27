#pragma once
#include "UIPanel.h"
#include "Player.h"
class PlayerUploadText : public UIPanel
{
public:
    // returns a bool when a valid file name is inserted in text box
    bool RenderFileUploadText(std::shared_ptr<Player>& player);
protected:
    // keep track if valid file was uploaded
    bool validFile = true;
    
};

