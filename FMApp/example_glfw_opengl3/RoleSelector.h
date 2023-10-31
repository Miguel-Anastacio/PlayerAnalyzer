#pragma once
#include "UIPanel.h"
#include <vector>
#include <unordered_map>
struct Role;
class RoleEditor;
class RoleSelector :  public UIPanel
{
public:
    std::vector<Role> AllRoles;
    RoleSelector(const bool& noMove, const bool& noResize, const bool& noCollapse, const std::string& name, const bool& visible);
    void RenderPanel() override;

    void SetRoleEditor(RoleEditor* editor);
    RoleEditor* GetRoleEditor();

    void SetRolesSelectedMap();

    void SetOriginalDBRef(const std::vector<Role>& db);
    void SetAllRoles(const std::vector<Role>& roles);
private:
    RoleEditor* MyRoleEditor = NULL;

    std::unordered_map<uint64_t, bool> RolesSelectedMap;
    uint64_t PreviousRoleID = 0;

    const std::vector<Role>* OriginalDB;
};

