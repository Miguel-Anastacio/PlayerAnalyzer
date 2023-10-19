#pragma once
#include "UIPanel.h"
#include <memory>
class Player;
class RoleEfficiencyPanel :public UIPanel
{
public:
    RoleEfficiencyPanel(const bool& noMove, const bool& noResize, const bool& noCollapse, const std::string& name, const bool& visible);

    void RenderPanel() override;


    void SetPlayerToDisplay(const std::shared_ptr<Player>& player);
protected:
    std::shared_ptr<Player> PlayerToDisplay;
};

