#pragma once
#include "PlayerAttributesPanel.h"
class PlayerAttributeComparison :  public PlayerAttributesPanel
{
public:
    PlayerAttributeComparison(const bool& noMove, const bool& noResize, const bool& noCollapse, const std::string& name, const bool& visible);
    void RenderPanel() override;

    void SetSecondPlayer(const std::shared_ptr<Player>& player);
protected:
    std::shared_ptr<Player> SecondPlayer;


};

