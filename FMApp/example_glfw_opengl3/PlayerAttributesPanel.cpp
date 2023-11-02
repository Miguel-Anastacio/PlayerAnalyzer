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
    if (FirstPlayer != nullptr)
    {
        ImGui::Text("Player Loaded: %s", FirstPlayer->GetName().c_str());
        const int bufferSize = 30;
        char inputBuffer[bufferSize] = "New Name"; // Buffer to store the text input
        ImGui::SetNextItemWidth(200);
        // ImGui InputText widget
        if (ImGui::InputText(" ", inputBuffer, bufferSize, ImGuiInputTextFlags_EnterReturnsTrue))
        {
            FirstPlayer->SetName(inputBuffer);
        }
    }
    RenderAttributeTable(FirstPlayer);
       
    ImGui::End();
}

void PlayerAttributesPanel::SetRoleSelected(Role* role)
{
    RoleSelected = role;
}

void PlayerAttributesPanel::SetFirstPlayer(Player* player)
{
    FirstPlayer = player;
}

void PlayerAttributesPanel::SetPlayerToDisplay(std::shared_ptr<Player> player)
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

void PlayerAttributesPanel::RenderAttributeTable(Player* player)
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
                    bool relevant = false;
                    // is attribute supposed to be higlighted
                    if (RoleSelected != NULL)
                    {
                        if (RoleSelected->ID != 0 && RoleSelected->IsAttributePartOfRole(technicalAtt[i].ID))
                            relevant = true;
                    }
                    // render technical attribute
                    RenderStringValuePairTableHiglighted(technicalAtt[i].Name, technicalAtt[i].Value, *AttributesHighligth, boldFont, relevant);

                    relevant = false;
                    // is attribute supposed to be higlighted
                    if (RoleSelected != NULL)
                    {
                        if (RoleSelected->ID != 0 && RoleSelected->IsAttributePartOfRole(mentalAtt[i].ID))
                            relevant = true;
                    }
                    // render mental attribute
                    RenderStringValuePairTableHiglighted(mentalAtt[i].Name, mentalAtt[i].Value, *AttributesHighligth, boldFont, relevant);

                    // render physical attribute
                    if (i < 8)
                    {
                        relevant = false;
                        // is attribute supposed to be higlighted
                        if (RoleSelected != NULL)
                        {
                            if (RoleSelected->ID != 0 && RoleSelected->IsAttributePartOfRole(physicalAtt[i].ID))
                                relevant = true;
                        }
                        RenderStringValuePairTableHiglighted(physicalAtt[i].Name, physicalAtt[i].Value, *AttributesHighligth, boldFont, relevant);
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

void PlayerAttributesPanel::RenderAttributeTable(std::shared_ptr<Player> player)
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
                    bool relevant = false;
                    // is attribute supposed to be higlighted
                    if (RoleSelected != NULL)
                    {
                        if (RoleSelected->ID != 0 && RoleSelected->IsAttributePartOfRole(technicalAtt[i].ID))
                            relevant = true;
                    }
                    // render technical attribute
                    RenderStringValuePairTableHiglighted(technicalAtt[i].Name, technicalAtt[i].Value, *AttributesHighligth, boldFont, relevant);

                    relevant = false;
                    // is attribute supposed to be higlighted
                    if (RoleSelected != NULL)
                    {
                        if (RoleSelected->ID != 0 && RoleSelected->IsAttributePartOfRole(mentalAtt[i].ID))
                            relevant = true;
                    }
                    // render mental attribute
                    RenderStringValuePairTableHiglighted(mentalAtt[i].Name, mentalAtt[i].Value, *AttributesHighligth, boldFont, relevant);

                    // render physical attribute
                    if (i < 8)
                    {
                        relevant = false;
                        // is attribute supposed to be higlighted
                        if (RoleSelected != NULL)
                        {
                            if (RoleSelected->ID != 0 && RoleSelected->IsAttributePartOfRole(physicalAtt[i].ID))
                                relevant = true;
                        }
                        RenderStringValuePairTableHiglighted(physicalAtt[i].Name, physicalAtt[i].Value, *AttributesHighligth, boldFont, relevant);
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

