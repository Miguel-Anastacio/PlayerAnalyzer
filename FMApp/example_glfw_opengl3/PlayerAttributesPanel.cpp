#include "PlayerAttributesPanel.h"
#include "Player.h"

PlayerAttributesPanel::PlayerAttributesPanel(const bool& noMove, const bool& noResize, const bool& noCollapse, const std::string& name, const bool& visible)
    : UIPanel(noMove, noResize, noCollapse, name, visible)
{
    const std::vector<int> ranges = { 4, 8, 12, 16, 20 };
    AttributesHighligth = std::make_shared<Highlight<int>>(ranges);
}

void PlayerAttributesPanel::RenderPanel()
{
    ImGuiIO& io = ImGui::GetIO();
    auto boldFont = io.Fonts->Fonts[0];
   
    ImGui::Begin(Name.c_str(), nullptr, window_flags);
    if (PlayerToDisplay != nullptr)
    {
        ImGui::Text("Player Loaded: %s", PlayerToDisplay->GetName().c_str());
        const int bufferSize = 30;
        char inputBuffer[bufferSize] = "New Name"; // Buffer to store the text input
        ImGui::SetNextItemWidth(200);
        // ImGui InputText widget
        if (ImGui::InputText(" ", inputBuffer, bufferSize, ImGuiInputTextFlags_EnterReturnsTrue))
        {
            PlayerToDisplay->SetName(inputBuffer);
        }
    }
    RenderAttributeTable(PlayerToDisplay);
       
    ImGui::End();
}

void PlayerAttributesPanel::SetPlayerToDisplay(const std::shared_ptr<Player>& player)
{
    PlayerToDisplay = player;
}

void PlayerAttributesPanel::SetPlayersHighlight(const std::shared_ptr<Highlight<int>>& newHiglight)
{
    AttributesHighligth = newHiglight;
}

std::shared_ptr<Highlight<int>> PlayerAttributesPanel::GetPlayersHighlight()
{
    return AttributesHighligth;
}

void PlayerAttributesPanel::RenderAttributeTable(const std::shared_ptr<Player>& player)
{
    ImGuiIO& io = ImGui::GetIO();
    auto boldFont = io.Fonts->Fonts[0];

    if (player != nullptr)
    {

        std::vector<Attribute> PlayerAttributes = player->GetPlayerAttributes();
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

                ImGui::TableSetupColumn("Technical", ImGuiTableColumnFlags_WidthFixed, headerSize);
                ImGui::TableSetupColumn("", ImGuiTableColumnFlags_WidthFixed, smallHeaderSize);
                ImGui::TableSetupColumn("Mental", ImGuiTableColumnFlags_WidthFixed, headerSize);
                ImGui::TableSetupColumn("", ImGuiTableColumnFlags_WidthFixed, smallHeaderSize);
                ImGui::TableSetupColumn("Physical", ImGuiTableColumnFlags_WidthFixed, headerSize);
                ImGui::TableSetupColumn("", ImGuiTableColumnFlags_WidthFixed, smallHeaderSize);
                ImGui::TableHeadersRow();
                ImGui::TableNextRow();
                ImGui::TableSetColumnIndex(0);


                for (int i = 0; i < 14; ++i)
                {
                    //ColorCodeTableItems(technicalAtt[i].Value, attHighlight);
                    // render technical attribute
                    RenderStringValuePairTable(technicalAtt[i].Name, technicalAtt[i].Value, *AttributesHighligth, boldFont);
                    // render mental attribute
                    RenderStringValuePairTable(mentalAtt[i].Name, mentalAtt[i].Value, *AttributesHighligth, boldFont);

                    // render physical attribute
                    if (i < 8)
                    {
                        RenderStringValuePairTable(physicalAtt[i].Name, physicalAtt[i].Value, *AttributesHighligth, boldFont);
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
}

