#include "SelectPlayers.h"
#include "Player.h"
#include "PlayerAttributeComparison.h"
SelectPlayers::SelectPlayers(const bool& noMove, const bool& noResize, const bool& noCollapse, const std::string& name, const bool& visible, const Image& image)
    : ImagesPanel(noMove, noResize, noCollapse, name, visible, image)
{
    FileImage.width = FileImage.width * 0.075;
    FileImage.height = FileImage.height * 0.05;

    //if (true)    window_flags |= ImGuiWindowFlags_NoFocusOnAppearing;
}

void SelectPlayers::RenderPanel()
{
    UpdatePlayersSelectedMap();
    ImGui::Begin(Name.c_str(), nullptr, window_flags);
    int index = 0;
    HelpMarker("Hold Ctrl to select multiple");
    for (auto& player : *PlayersUploaded)
    {
        ImGui::PushID(player.GetUniqueID());

        ImVec2 size = ImGui::CalcTextSize(player.GetName().c_str());
        size.x = size.x + FileImage.width;
        if (size.x < 200)
            size.x = ImGui::GetContentRegionMax().x;
        size.y = FileImage.height + 5;

        ImVec2 alignment = ImVec2(0, 0.5f);
        ImGui::PushStyleVar(ImGuiStyleVar_SelectableTextAlign, alignment);
        if (ImGui::Selectable(player.GetName().c_str(), PlayersSelectedMap.at(player.GetUniqueID()), 0, size))
        {
            // control is not held just remove every player and add this one
            if (!ImGui::GetIO().KeyCtrl)
            {
                for (auto& pair : PlayersSelectedMap)
                {
                    pair.second = false;
                }
                PlayersSelectedIndex.clear();
                PlayersSelectedMap.at(player.GetUniqueID()) = true;
                PlayersSelectedIndex.emplace_back(index);
            }
            // control was held but player was already selected
            // so remove this player from selected vector
            else if (PlayersSelectedMap.at(player.GetUniqueID()))
            {
                PlayersSelectedMap.at(player.GetUniqueID()) = false;
                for (int i = 0; i < PlayersSelectedIndex.size(); i++)
                {
                    if (PlayersSelectedIndex[i] == index)
                    {
                        PlayersSelectedIndex.erase(PlayersSelectedIndex.begin() + i);
                        break;
                    }
                }
            }
            // control held and player was not already selected
            else if (!PlayersSelectedMap.at(player.GetUniqueID()))
            {
                PlayersSelectedMap.at(player.GetUniqueID()) = true;
                PlayersSelectedIndex.emplace_back(index);
            }

        }
        ImGui::PopStyleVar();

        //ImGui::SetItemTooltip("Press to load");
        ImGui::SameLine(ImGui::CalcTextSize(player.GetName().c_str()).x + 15.0f);

        if (ImGui::ImageButton("Image Button", (void*)(intptr_t)FileImage.FileTextureID, ImVec2(FileImage.width, FileImage.height)))
        {
            if (ImGui::GetIO().KeyCtrl)
            {
                for (auto& pair : PlayersSelectedMap)
                {
                    pair.second = false;
                }
                PlayersSelectedIndex.clear();

            }
            if(!PlayersSelectedMap.at(player.GetUniqueID()))
                PlayersSelectedIndex.emplace_back(index);
            PlayersSelectedMap.at(player.GetUniqueID()) = true;
        }
        //ImGui::SetItemTooltip("Press to load");
        ImGui::PopID();
        index++;
    }

    if (PlayersSelectedIndex.size() == 2)
    {
        if (ImGui::Button("Compare Players"))
        {
            AttributeComparison->SetFirstPlayer(&(*PlayersUploaded)[PlayersSelectedIndex[0]]);
            AttributeComparison->SetSecondPlayer(&(*PlayersUploaded)[PlayersSelectedIndex[1]]);

            for (auto& pair : PlayersSelectedMap)
            {
                pair.second = false;
            }
            PlayersSelectedIndex.clear();
        }
    }


    ImGui::End();
}

void SelectPlayers::SetPlayersUploaded(std::vector<Player>* players)
{
    PlayersUploaded = players;
   
   
}

void SelectPlayers::SetAttributeComparisonRef(PlayerAttributeComparison* ref)
{
    AttributeComparison = ref;
}

void SelectPlayers::UpdatePlayersSelectedMap()
{
    // goes through all the player and sees id there is a new one
    for (auto pl : *PlayersUploaded)
    {
        try
        {
            bool value = PlayersSelectedMap.at(pl.GetUniqueID());
            
        }
        catch (const std::out_of_range& e)
        {
            PlayersSelectedMap.emplace(pl.GetUniqueID(), false);
        }
    }

}
