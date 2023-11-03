#include "PlayerAttributeComparison.h"
#include "Player.h"
PlayerAttributeComparison::PlayerAttributeComparison(const bool& noMove, const bool& noResize, const bool& noCollapse, const std::string& name, const bool& visible)
    : PlayerAttributesPanel(noMove, noResize, noCollapse, name, visible)
{

}

void PlayerAttributeComparison::RenderPanel()
{
    float start = 260;
    float tableLength = 640;
    ImGui::Begin(Name.c_str(), nullptr, window_flags);
    if (FirstPlayer != NULL && SecondPlayer != NULL)
    {
        ImGui::Separator();
        ImGui::Indent(start);
        ImGui::Text("Player 1");
        ImGui::SameLine(start, tableLength);
        ImGui::Text("Player 2");
        ImGui::Unindent(start);
        ImGui::Separator();
        ImGui::Spacing();
        ImGui::Spacing();
        ImGui::Spacing();
        RenderAttributeTable(FirstPlayer);
        ImGui::SameLine();
        RenderAttributeTable(SecondPlayer);
        ImGui::Spacing();
        ImGui::Spacing();
        ImGui::Spacing();
        RenderRoleSelectedEfficiency();
    }
    ImGui::End();
}

void PlayerAttributeComparison::SetSecondPlayer(Player* player)
{
    SecondPlayer = player;
}


void PlayerAttributeComparison::RenderRoleSelectedEfficiency()
{
    static bool bg = true;
    static ImGuiTableFlags flags = ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg;
    if (bg)   flags |= ImGuiTableFlags_Borders;

    float headerSize = 150.0f;
    if (ImGui::BeginTable("Comparison", 3, flags, ImVec2(600, 0)))
    {
        ImGui::TableSetupColumn("Role", ImGuiTableColumnFlags_WidthFixed, headerSize*2);
        ImGui::TableSetupColumn(FirstPlayer->GetName().c_str(), ImGuiTableColumnFlags_WidthFixed, headerSize);
        ImGui::TableSetupColumn(SecondPlayer->GetName().c_str(), ImGuiTableColumnFlags_WidthFixed, headerSize);
        ImGui::TableHeadersRow();
        ImGui::TableNextRow();
        ImGui::TableSetColumnIndex(0);

        if (RoleSelected != NULL)
        {
            RoleEfficiency player1Eff = FirstPlayer->GetEfficiencyOfRole(RoleSelected->ID, RoleSelected->TypeEnum);
            RoleEfficiency player2Eff = SecondPlayer->GetEfficiencyOfRole(RoleSelected->ID, RoleSelected->TypeEnum);

            ImGui::Text(RoleSelected->Name.c_str());
            ImGui::TableNextColumn();
            ImGui::Text("%.2f", player1Eff.Value);
            ImGui::TableNextColumn();
            ImGui::Text("%.2f", player2Eff.Value);
        }
        else
        {
            ImGui::Text("No role selected");
            ImGui::TableNextColumn();
            ImGui::Text("%.2f", 0.0f);
            ImGui::TableNextColumn();
            ImGui::Text("%.2f", 0.0f);
        }

        ImGui::EndTable();
    }
}
