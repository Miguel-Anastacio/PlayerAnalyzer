#pragma once
#include "UIPanel.h"
#include <memory>
class Player;
class PlayerAttributesPanel: public UIPanel
{
public:
    PlayerAttributesPanel(const bool& noMove, const bool& noResize, const bool& noCollapse, const std::string& name, const bool& visible);

    void RenderPanel() override;



    void SetPlayerToDisplay(const std::shared_ptr<Player>& player);
    void SetPlayersHighlight(const  std::shared_ptr<Highlight<int>>& newHiglight);
    std::shared_ptr<Highlight<int>> GetPlayersHighlight();

protected:

    void RenderAttributeTable(const std::shared_ptr<Player>& player);

    std::shared_ptr<Player> PlayerToDisplay;
    std::shared_ptr<Highlight<int>> AttributesHighligth;
   

};

