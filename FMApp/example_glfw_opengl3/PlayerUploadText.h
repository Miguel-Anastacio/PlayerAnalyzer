#pragma once
#include "UIPanel.h"
#include "Player.h"
class PlayerUploadText : public UIPanel
{
public:
    void RenderFileUploadText(std::shared_ptr<Player>& player);
protected:
    // keep track if valid file was uploaded
    bool validFile = true;
    
};

