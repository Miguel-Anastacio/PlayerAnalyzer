#include "RoleEfficiencyPanel.h"
#include "Player.h"

RoleEfficiencyPanel::RoleEfficiencyPanel(const bool& noMove, const bool& noResize, const bool& noCollapse, const std::string& name, const bool& visible)
    : UIPanel(noMove, noResize, noCollapse, name, visible)
{

}

void RoleEfficiencyPanel::RenderPanel()
{
    ImGui::Begin(Name.c_str(), nullptr, window_flags);

    if (PlayerToDisplay != nullptr)
    {
        static bool bg = true;
        static ImGuiTableFlags flags = ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg;
        if (bg)   flags |= ImGuiTableFlags_Borders;
        if (ImGui::BeginTable("table2", 3, flags))
        {
            int attributesIndex = 0;
            float headerSize = 320.0f;
            ImGui::TableSetupColumn("Defensive", ImGuiTableColumnFlags_WidthFixed, headerSize);
            ImGui::TableSetupColumn("Midfield", ImGuiTableColumnFlags_WidthFixed, headerSize);
            ImGui::TableSetupColumn("Attacking", ImGuiTableColumnFlags_WidthFixed, headerSize);
            ImGui::TableHeadersRow();
            ImGui::TableNextRow();

            // Fill the first column first
            std::vector<RoleEfficiency> DefensiveRoles = PlayerToDisplay->GetDefensiveRoles();
            for (const auto& role : DefensiveRoles)
            {
                //ImGui::TableNextRow();
                ImGui::TableSetColumnIndex(0);
                //ImGui::Text("%-20s %d", PlayerAttributes[attributesIndex].Name.c_str(), PlayerAttributes[attributesIndex].Value);
                ImGui::Text("%-35s %.2f", role.RoleName.c_str(), role.Value);

            }

            std::vector<RoleEfficiency> Midfield = PlayerToDisplay->GetMidfieldRoles();
            for (const auto& role : Midfield)
            {
                //ImGui::TableNextRow();
                ImGui::TableSetColumnIndex(1);
                //ImGui::Text("%-20s %d", PlayerAttributes[attributesIndex].Name.c_str(), PlayerAttributes[attributesIndex].Value);
                ImGui::Text("%-35s %.2f", role.RoleName.c_str(), role.Value);
            }

            std::vector<RoleEfficiency> Attacking = PlayerToDisplay->GetAttackingRoles();
            for (const auto& role : Attacking)
            {
                //ImGui::TableNextRow();
                ImGui::TableSetColumnIndex(2);
                //ImGui::Text("%-20s %d", PlayerAttributes[attributesIndex].Name.c_str(), PlayerAttributes[attributesIndex].Value);
                ImGui::Text("%-35s %.2f", role.RoleName.c_str(), role.Value);
            }

            ImGui::EndTable();
        }


        ImGui::Spacing();
        ImGui::Separator();
        RoleEfficiency temp = PlayerToDisplay->GetBestPlayerRole();
        ImGui::Text("Player Best Role: %-35s  %f", temp.RoleName.c_str(), temp.Value);
        ImGui::Separator();
        ImGui::Spacing();
    }
    ImGui::End();

}

void RoleEfficiencyPanel::SetPlayerToDisplay(const std::shared_ptr<Player>& player)
{
    PlayerToDisplay = player;
}
