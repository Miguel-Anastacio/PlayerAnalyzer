#include "PlayerAttributesPanel.h"
#include "Player.h"

PlayerAttributesPanel::PlayerAttributesPanel(const bool& noMove, const bool& noResize, const bool& noCollapse, const std::string& name, const bool& visible)
    : UIPanel(noMove, noResize, noCollapse, name, visible)
{

}

void PlayerAttributesPanel::RenderPanel()
{
    ImGuiIO& io = ImGui::GetIO();
    auto boldFont = io.Fonts->Fonts[0];

    ImGui::Begin(Name.c_str(), nullptr, window_flags);

    if (PlayerToDisplay != nullptr)
    {
        std::vector<Attribute> PlayerAttributes = PlayerToDisplay->GetPlayerAttributes();
        Attribute technicalAtt[14];
        Attribute mentalAtt[14];
        Attribute physicalAtt[8];
        if (PlayerAttributes.size() > 0)
        {
            for (int i = 0; i < 14; i++)
            {
                technicalAtt[i] = PlayerAttributes[i];
            }
            for (int i = 0; i < 14; i++)
            {
                mentalAtt[i] = PlayerAttributes[i + 14];
            }
            for (int i = 0; i < 8; i++)
            {
                physicalAtt[i] = PlayerAttributes[i + 28];
            }

        }


        static bool bg = true;
        static ImGuiTableFlags flags = ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg;
        if (bg)   flags |= ImGuiTableFlags_Borders;

        if (PlayerAttributes.size() > 0)
        {
            float headerSize = 165.0f;
            float smallHeaderSize = 30.0f;
            
            if (ImGui::BeginTable("table2", 6, flags, ImVec2(640, 0)))
            {
                int attributesIndex = 0;
                ImGui::TableSetupColumn("Technical", ImGuiTableColumnFlags_WidthFixed, headerSize);
                ImGui::TableSetupColumn("", ImGuiTableColumnFlags_WidthFixed, smallHeaderSize);
                ImGui::TableSetupColumn("Mental", ImGuiTableColumnFlags_WidthFixed, headerSize);
                ImGui::TableSetupColumn("", ImGuiTableColumnFlags_WidthFixed, smallHeaderSize);
                ImGui::TableSetupColumn("Physical", ImGuiTableColumnFlags_WidthFixed, headerSize);
                ImGui::TableSetupColumn("", ImGuiTableColumnFlags_WidthFixed, smallHeaderSize);
                ImGui::TableHeadersRow();
                ImGui::TableNextRow();
                ImGui::TableSetColumnIndex(0);

                //for (int column = 0; column < 3; column++)
                //{
                //    for (int i = 0; i < 14; ++i)
                //    {
                //        //ImGui::TableNextRow();
                //        ImGui::TableSetColumnIndex(column);
                //        if (attributesIndex >= PlayerAttributes.size())
                //            break;
                //        ImGui::Text("%-20s %d", PlayerAttributes[attributesIndex].Name.c_str(), PlayerAttributes[attributesIndex].Value);
                //        attributesIndex++;
                //    }
                //}
                std::vector<int> thresholdAtt = { 4, 8, 12, 16, 20 };
                Highlight<int> attHighlight(thresholdAtt);

  
                for (int i = 0; i < 14; ++i)
                {
                    //ColorCodeTableItems(technicalAtt[i].Value, attHighlight);
                    // render technical attribute
                    RenderStringValuePairTable(technicalAtt[i].Name, technicalAtt[i].Value, attHighlight, boldFont);
                    // render mental attribute
                    RenderStringValuePairTable(mentalAtt[i].Name, mentalAtt[i].Value, attHighlight, boldFont);

                    // render physical attribute
                    if (i < 8)
                    {
                        RenderStringValuePairTable(physicalAtt[i].Name, physicalAtt[i].Value, attHighlight, boldFont);
                    }
                    else
                    {
                        ImGui::TableNextColumn();
                        ImGui::TableNextColumn();
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

