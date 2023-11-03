#pragma once
#include "PlayerAttributesPanel.h"
struct Role;
class PlayerAttributeComparison :  public PlayerAttributesPanel
{
public:
    PlayerAttributeComparison(const bool& noMove, const bool& noResize, const bool& noCollapse, const std::string& name, const bool& visible);
    void RenderPanel() override;

    void SetSecondPlayer( Player* player);

    void SetEfficiencyHiglight(std::shared_ptr<Highlight<float>>& highlight);
    void RenderRoleSelectedEfficiency();

protected:
    Player* SecondPlayer = NULL;

    std::shared_ptr<Highlight<float>> EfficiencyHighligth;

};

