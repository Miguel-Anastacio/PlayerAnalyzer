#include "RoleSelector.h"
#include "Define.h"
#include "RoleEditor.h"
RoleSelector::RoleSelector(const bool& noMove, const bool& noResize, const bool& noCollapse, const std::string& name, const bool& visible )
    : UIPanel(noMove, noResize, noCollapse, name, visible)
{
    //RoleSelected = new Role();
    
}

RoleSelector::~RoleSelector()
{
   /* if (RoleSelected != NULL)
    {
        delete RoleSelected;
    }*/
}

void RoleSelector::RenderPanel()
{
    ImGui::Begin(Name.c_str(), nullptr, window_flags);
    if (ImGui::TreeNode("Defensive"))
    {
        ImGui::Indent();
        for (auto& role : *AllRoles)
        {
            if (role.TypeEnum == Defensive)
            {
                bool button = ImGui::Selectable(role.Name.c_str(), RolesSelectedMap.at(role.ID));
                if (role.EditedFlag)
                {
                    ImGui::SetItemTooltip("This role was edited");
                    ImGui::SameLine();
                    ImGui::Text("(*)");
                    ImGui::SetItemTooltip("This role was edited");
                }
                if (button)
                {
                    RolesSelectedMap.at(PreviousRoleID) = false;
                    RolesSelectedMap.at(role.ID) = true;
                    PreviousRoleID = role.ID;


                    if (MyRoleEditor != NULL)
                    {
                        MyRoleEditor->SetCurrentRole(role);
                        MyRoleEditor->SetContentsVisibility(true);
                    }
                    //*RoleSelected = role;
                    RoleSelected = &role;
                }
              
            }
        }
        ImGui::Unindent();
        ImGui::TreePop();
    }
    if (ImGui::TreeNode("Midfield"))
    {
        ImGui::Indent();

        for (auto& role : *AllRoles)
        {
            if (role.TypeEnum == Midfield)
            {

                bool button = ImGui::Selectable(role.Name.c_str(), RolesSelectedMap.at(role.ID));
                if (role.EditedFlag)
                {
                    ImGui::SetItemTooltip("This role was edited");
                    ImGui::SameLine();
                    ImGui::Text("(*)");
                    ImGui::SetItemTooltip("This role was edited");
                }
                if (button)
                {
                    RolesSelectedMap.at(PreviousRoleID) = false;
                    RolesSelectedMap.at(role.ID) = true;
                    PreviousRoleID = role.ID;


                    if (MyRoleEditor != NULL)
                    {
                        MyRoleEditor->SetCurrentRole(role);
                        MyRoleEditor->SetContentsVisibility(true);
                    }
                    //*RoleSelected = role;
                    RoleSelected = &role;

                }
            }
        }
        ImGui::Unindent();
        ImGui::TreePop();
    }
    if (ImGui::TreeNode("Attacking"))
    {
        ImGui::Indent();

        for (auto& role : *AllRoles)
        {
            if (role.TypeEnum == Attacking)
            {

                bool button = ImGui::Selectable(role.Name.c_str(), RolesSelectedMap.at(role.ID));
                if (role.EditedFlag)
                {
                    ImGui::SetItemTooltip("This role was edited");
                    ImGui::SameLine();
                    ImGui::Text("(*)");
                    ImGui::SetItemTooltip("This role was edited");
                }
                if (button)
                {
                    RolesSelectedMap.at(PreviousRoleID) = false;
                    RolesSelectedMap.at(role.ID) = true;
                    PreviousRoleID = role.ID;

                    // role selector when it is in the edit roles menu has a reference to the role editor
                    if (MyRoleEditor != NULL)
                    {
                        MyRoleEditor->SetCurrentRole(role);
                        MyRoleEditor->SetContentsVisibility(true);
                    }

                    //*RoleSelected = role;
                    RoleSelected = &role;

                }
            }
        }
        ImGui::Unindent();
        ImGui::TreePop();
    }

    ImGui::Spacing();
    ImGui::Spacing();
    ImGui::Spacing();
    ImGui::Spacing();
    ImGui::Spacing();
    ImGui::Spacing();

    if (MyRoleEditor != NULL)
    {
        if (ImGui::Button("Reset All Roles"))
        {
            AllRoles = &OriginalDB;
        }
    }

    
    ImGui::End();
    if (MyRoleEditor != NULL)
    {
        MyRoleEditor->RenderPanel();
        // role editor might change the role selected so update it
        if (MyRoleEditor->GetCurrentRole() != NULL && MyRoleEditor->GetCurrentRole()->EditedFlag)
        {
            //EditorChangedRole = true;
        }
    }
    
}

void RoleSelector::SetRoleEditor(RoleEditor* editor)
{
    MyRoleEditor = editor;
}

RoleEditor* RoleSelector::GetRoleEditor()
{
    return MyRoleEditor;
}

void RoleSelector::SetRolesSelectedMap()
{
    for (const auto role : *AllRoles)
    {
        RolesSelectedMap.emplace(role.ID, false);
    }
    PreviousRoleID = (*AllRoles)[0].ID;
}

void RoleSelector::SetAllRoles(std::vector<Role>& roles)
{
    AllRoles = &roles;
    //OriginalDB = roles;
    SetRolesSelectedMap();
}

Role* RoleSelector::GetRoleSelected()
{
    return RoleSelected;
}




void RoleSelector::SetOriginalDBRef(std::vector<Role>& db)
{
    OriginalDB = db;
}
