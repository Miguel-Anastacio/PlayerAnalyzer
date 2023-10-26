#include "PlayerAttributesPanel.h"
#include "Player.h"

PlayerAttributesPanel::PlayerAttributesPanel(const bool& noMove, const bool& noResize, const bool& noCollapse, const std::string& name, const bool& visible)
    : UIPanel(noMove, noResize, noCollapse, name, visible)
{

}

void PlayerAttributesPanel::RenderPanel()
{
    //// setup flags for file uploading window
    ImGui::Begin(Name.c_str(), nullptr, window_flags);

    if (PlayerToDisplay != nullptr)
    {
        std::vector<Attribute> PlayerAttributes = PlayerToDisplay->GetPlayerAttributes();

        static bool bg = true;
        static ImGuiTableFlags flags = ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg;
        if (bg)   flags |= ImGuiTableFlags_Borders;

        if (PlayerAttributes.size() > 0)
        {
            float headerSize = 165.0f;
            ImGui::SetNextItemWidth(3 * headerSize);
            if (ImGui::BeginTable("table2", 3, flags, ImVec2(520, 0)))
            {
                int attributesIndex = 0;
                ImGui::TableSetupColumn("Technical", ImGuiTableColumnFlags_WidthFixed, headerSize);
                ImGui::TableSetupColumn("Mental", ImGuiTableColumnFlags_WidthFixed, headerSize);
                ImGui::TableSetupColumn("Physical", ImGuiTableColumnFlags_WidthFixed, headerSize);
                ImGui::TableHeadersRow();
                ImGui::TableNextRow();

                for (int column = 0; column < 3; column++)
                {
                    for (int i = 0; i < 14; ++i)
                    {
                        //ImGui::TableNextRow();
                        ImGui::TableSetColumnIndex(column);
                        if (attributesIndex >= PlayerAttributes.size())
                            break;
                        ImGui::Text("%-20s %d", PlayerAttributes[attributesIndex].Name.c_str(), PlayerAttributes[attributesIndex].Value);
                        attributesIndex++;
                    }
                }

                ImGui::EndTable();
            }
        }
    }
    ImGui::End();
}

void PlayerAttributesPanel::SetPlayerToDisplay(const std::shared_ptr<Player>& player)
{
    PlayerToDisplay = player;
}
