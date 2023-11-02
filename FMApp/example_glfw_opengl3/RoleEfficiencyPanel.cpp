#include "RoleEfficiencyPanel.h"
#include "Player.h"

RoleEfficiencyPanel::RoleEfficiencyPanel(const bool& noMove, const bool& noResize, const bool& noCollapse, const std::string& name, const bool& visible)
    : UIPanel(noMove, noResize, noCollapse, name, visible)
{
    const std::vector<float> ranges = { 20, 40, 60, 80, 100 };
    EfficiencyHighligth = std::make_shared<Highlight<float>>(ranges);

    RoleSelected = new Role();
}

RoleEfficiencyPanel::~RoleEfficiencyPanel()
{
    if (RoleSelected != NULL)
    {
        delete RoleSelected;
    }
}

void RoleEfficiencyPanel::RenderPanel()
{
    ImGuiIO& io = ImGui::GetIO();
    auto boldFont = io.Fonts->Fonts[0];

    ImGui::Begin(Name.c_str(), nullptr, window_flags);

    if (PlayerToDisplay != nullptr)
    {
        static bool bg = true;
        static ImGuiTableFlags flags = ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg;
        if (bg)   flags |= ImGuiTableFlags_Borders;
        if (ImGui::BeginTable("table2", 6, flags, ImVec2(1105,0)))
        {
            int attributesIndex = 0;
            float headerSize = 300.0f;
            float smallHeaderSize = 50.0f;
            ImGui::PushFont(boldFont);
            ImGui::TableSetupColumn("Defensive", ImGuiTableColumnFlags_WidthFixed, headerSize);
            ImGui::TableSetupColumn("", ImGuiTableColumnFlags_WidthFixed, smallHeaderSize);
            ImGui::TableSetupColumn("Midfield", ImGuiTableColumnFlags_WidthFixed, headerSize);
            ImGui::TableSetupColumn("", ImGuiTableColumnFlags_WidthFixed, smallHeaderSize);
            ImGui::TableSetupColumn("Attacking", ImGuiTableColumnFlags_WidthFixed, headerSize);
            ImGui::TableSetupColumn("", ImGuiTableColumnFlags_WidthFixed, smallHeaderSize);
            
            ImGui::TableHeadersRow();
            ImGui::TableNextRow();
            ImGui::TableSetColumnIndex(0);
            ImGui::PopFont();


            std::vector<RoleEfficiency> DefensiveRoles = PlayerToDisplay->GetDefensiveRoles();
            std::vector<RoleEfficiency> MidfieldRoles = PlayerToDisplay->GetMidfieldRoles();
            std::vector<RoleEfficiency> AttackingRoles = PlayerToDisplay->GetAttackingRoles();
            for (int i = 0; i < MidfieldRoles.size(); i++)
            {
                if (i < DefensiveRoles.size())
                {
                    //RenderStringValuePairTable(DefensiveRoles[i].RoleName, DefensiveRoles[i].Value, effHighlight, boldFont);
                    if (RenderStringValuePairTableAsSelectable(DefensiveRoles[i].RoleName, DefensiveRoles[i].Value, *EfficiencyHighligth, boldFont))
                    {
                        RoleSelected->ID = DefensiveRoles[i].ID;
                        RoleSelected->TypeEnum = Defensive;
                    }
                }
                else
                {
                    ImGui::TableNextColumn();
                    ImGui::TableNextColumn();
                }
                
                //RenderStringValuePairTable(MidfieldRoles[i].RoleName, MidfieldRoles[i].Value, effHighlight, boldFont);
                if (RenderStringValuePairTableAsSelectable(MidfieldRoles[i].RoleName, MidfieldRoles[i].Value, *EfficiencyHighligth, boldFont))
                {
                    RoleSelected->ID = MidfieldRoles[i].ID;
                    RoleSelected->TypeEnum = Midfield;

                }

                if (i < AttackingRoles.size())
                {
                    //RenderStringValuePairTable(AttackingRoles[i].RoleName, AttackingRoles[i].Value, effHighlight, boldFont);
                    if (RenderStringValuePairTableAsSelectable(AttackingRoles[i].RoleName, AttackingRoles[i].Value, *EfficiencyHighligth, boldFont))
                    {
                        RoleSelected->ID = AttackingRoles[i].ID;
                        RoleSelected->TypeEnum = Attacking;
                    }
                }
                else
                {
                    ImGui::TableNextColumn();
                    ImGui::TableNextColumn();
                }

            }


            //// Fill the first column first
            //for (const auto& role : DefensiveRoles)
            //{
            //    //ImGui::TableNextRow();
            //    ImGui::TableSetColumnIndex(0);
            //    //ImGui::Text("%-20s %d", PlayerAttributes[attributesIndex].Name.c_str(), PlayerAttributes[attributesIndex].Value);
            //    ImGui::Text("%-35s %.2f", role.RoleName.c_str(), role.Value);

            //}

            //std::vector<RoleEfficiency> Midfield = PlayerToDisplay->GetMidfieldRoles();
            //for (const auto& role : Midfield)
            //{
            //    //ImGui::TableNextRow();
            //    ImGui::TableSetColumnIndex(1);
            //    //ImGui::Text("%-20s %d", PlayerAttributes[attributesIndex].Name.c_str(), PlayerAttributes[attributesIndex].Value);
            //    ImGui::Text("%-35s %.2f", role.RoleName.c_str(), role.Value);
            //}

            //for (const auto& role : Attacking)
            //{
            //    //ImGui::TableNextRow();
            //    ImGui::TableSetColumnIndex(2);
            //    //ImGui::Text("%-20s %d", PlayerAttributes[attributesIndex].Name.c_str(), PlayerAttributes[attributesIndex].Value);
            //    ImGui::Text("%-35s %.2f", role.RoleName.c_str(), role.Value);
            //}

            ImGui::EndTable();
        }


        ImGui::Spacing();
        ImGui::Separator();
        RoleEfficiency temp = PlayerToDisplay->GetBestPlayerRole();
        ImGui::Indent(50.0);
        ImGui::Text("Player Best Role : ");
        ImGui::SameLine();
        ImGui::TextColored(EfficiencyHighligth->GetColors()[4], " %-35s  %.2f", temp.RoleName.c_str(), temp.Value);
        ImGui::Unindent(50.0);
        ImGui::Separator();
        ImGui::Spacing();
    }
    ImGui::End();

}

std::shared_ptr<Highlight<float>> RoleEfficiencyPanel::GetEfficiencyHighlight()
{
    return EfficiencyHighligth;
}

void RoleEfficiencyPanel::SetPlayerToDisplay(const std::shared_ptr<Player>& player)
{
    PlayerToDisplay = player;
}

Role* RoleEfficiencyPanel::GetRoleSelected()
{
    return RoleSelected;
}
