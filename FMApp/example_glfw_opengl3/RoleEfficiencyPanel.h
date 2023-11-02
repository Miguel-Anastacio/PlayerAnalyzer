#pragma once
#include "UIPanel.h"
#include <memory>
#include<unordered_map>
class Player;
struct Role;
struct RoleEfficiency;
class RoleEfficiencyPanel :public UIPanel
{
public:
    RoleEfficiencyPanel(const bool& noMove, const bool& noResize, const bool& noCollapse, const std::string& name, const bool& visible);
    ~RoleEfficiencyPanel();
    void RenderPanel() override;

    std::shared_ptr<Highlight<float>> GetEfficiencyHighlight();
    void SetPlayerToDisplay(Player* player);

    Role* GetRoleSelected();
    void InitRoleSelectedMap(const std::vector<Role>& allRoles);
protected:
    void UpdateEfficiencyValues();

    std::vector<RoleEfficiency> DefensiveRoles;
    std::vector<RoleEfficiency> MidfieldRoles;
    std::vector<RoleEfficiency> AttackingRoles;


    Player* PlayerToDisplay = NULL;
    std::shared_ptr<Highlight<float>> EfficiencyHighligth;

    Role* RoleSelected = NULL;
    std::unordered_map<uint64_t, bool> RoleSelectedMap;
    uint64_t PreviousRoleID = 0;
};

