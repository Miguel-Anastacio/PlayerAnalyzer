#pragma once
#include "UIPanel.h"
#include <vector>
#include <unordered_map>
struct Role;
class RoleEditor;
class RoleSelector :  public UIPanel
{
public:
    //static bool EditorChangedRole;
    std::vector<Role>* AllRoles;
    RoleSelector(const bool& noMove, const bool& noResize, const bool& noCollapse, const std::string& name, const bool& visible);
    ~RoleSelector();
    void RenderPanel() override;

    void SetRoleEditor(RoleEditor* editor);
    RoleEditor* GetRoleEditor();

    void SetRolesSelectedMap();

    void SetOriginalDBRef(std::vector<Role>& db);
    void SetAllRoles(std::vector<Role>& roles);

    Role* GetRoleSelected();
    //void UpdateRoleSelected();

private:
    RoleEditor* MyRoleEditor = NULL;
    Role* RoleSelected = NULL;

    std::unordered_map<uint64_t, bool> RolesSelectedMap;
    uint64_t PreviousRoleID = 0;

     std::vector<Role> OriginalDB;
};

