#pragma once
#include "UIPanel.h"
#include <memory>
class Player;
struct Role;
class RoleEfficiencyPanel :public UIPanel
{
public:
    RoleEfficiencyPanel(const bool& noMove, const bool& noResize, const bool& noCollapse, const std::string& name, const bool& visible);
    ~RoleEfficiencyPanel();
    void RenderPanel() override;

    std::shared_ptr<Highlight<float>> GetEfficiencyHighlight();
    void SetPlayerToDisplay(Player* player);

    Role* GetRoleSelected();
protected:
    Player* PlayerToDisplay = NULL;
    std::shared_ptr<Highlight<float>> EfficiencyHighligth;

    Role* RoleSelected = NULL;
};

