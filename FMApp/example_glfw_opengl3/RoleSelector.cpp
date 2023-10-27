#include "RoleSelector.h"
#include "Define.h"
#include "RoleEditor.h"
RoleSelector::RoleSelector(const bool& noMove, const bool& noResize, const bool& noCollapse, const std::string& name, const bool& visible )
    : UIPanel(noMove, noResize, noCollapse, name, visible)
{
}

void RoleSelector::RenderPanel()
{
    ImGui::Begin(Name.c_str(), nullptr, window_flags);

    ImGuiStyle& style = ImGui::GetStyle();
    style.Colors[ImGuiCol_Button] = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);

    if (ImGui::TreeNode("Defensive"))
    {
        ImGui::Indent();
        for (auto& role : AllRoles)
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

                    MyRoleEditor->SetCurrentRole(role);
                    MyRoleEditor->SetContentsVisibility(true);
                }
              
            }
        }
        ImGui::Unindent();
        ImGui::TreePop();
    }
    if (ImGui::TreeNode("Midfield"))
    {
        ImGui::Indent();

        for (auto& role : AllRoles)
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

                    MyRoleEditor->SetCurrentRole(role);
                    MyRoleEditor->SetContentsVisibility(true);
                }
            }
        }
        ImGui::Unindent();
        ImGui::TreePop();
    }
    if (ImGui::TreeNode("Attacking"))
    {
        ImGui::Indent();

        for (auto& role : AllRoles)
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

                    MyRoleEditor->SetCurrentRole(role);
                    MyRoleEditor->SetContentsVisibility(true);
                }
            }
        }
        ImGui::Unindent();
        ImGui::TreePop();
    }

    style = ImGui::GetStyle();
    style.Colors[ImGuiCol_Button] = ImVec4(0.2f, 0.4f, 0.6f, 1.0f);
    ImGui::End();

    MyRoleEditor->RenderPanel();

}

void RoleSelector::SetRoleEditor(RoleEditor* editor)
{
    MyRoleEditor = editor;
}

void RoleSelector::SetRolesSelectedMap()
{
    for (const auto role : AllRoles)
    {
        RolesSelectedMap.emplace(role.ID, false);
       
    }
    PreviousRoleID = AllRoles[0].ID;
}
