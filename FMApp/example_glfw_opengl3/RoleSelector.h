#pragma once
#include "UIPanel.h"
#include <vector>
struct Role;
class RoleEditor;
class RoleSelector :  public UIPanel
{
public:
    std::vector<Role> AllRoles;
    RoleSelector(const bool& noMove, const bool& noResize, const bool& noCollapse, const std::string& name, const bool& visible);
    void RenderPanel() override;

    void SetRoleEditor(RoleEditor* editor);
private:
    RoleEditor* MyRoleEditor;
};

