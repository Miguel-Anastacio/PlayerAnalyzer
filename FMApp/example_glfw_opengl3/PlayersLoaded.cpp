#include "PlayersLoaded.h"
#include "Player.h"
PlayersLoaded::PlayersLoaded(const bool& noMove, const bool& noResize, const bool& noCollapse, const std::string& name, const bool& visible, const Image& image)
    : ImagesPanel(noMove, noResize, noCollapse, name, visible, image)
{
    FileImage.width = FileImage.width * 0.075;
    FileImage.height = FileImage.height * 0.05;
}

void PlayersLoaded::RenderPanel()
{
    ImGui::Begin(Name.c_str(), nullptr, window_flags);
    int columns = 0;
    
    for (auto& player : *PlayersUploaded)
    {
        if (ImGui::ImageButton(player->GetName().c_str(), (void*)(intptr_t)FileImage.FileTextureID, ImVec2(FileImage.width, FileImage.height)))
        {
            ContentsVisibility = true;
            FileToUse = player->GetName();
            CurrentPlayer = player;
        }

        ImGui::SetItemTooltip("Press to load");
        ImGui::SameLine(65.0f);
        //ImGui::Spacing();
        //ImGui::Spacing();
        if (ImGui::Selectable(player->GetName().c_str(), ContentsVisibility))
        {
            ContentsVisibility = true;
            FileToUse = player->GetName();
            *CurrentPlayer = *player;

        }
        ImGui::SetItemTooltip("Press to load");

        //ImGui::Text(player->GetName().c_str());
    }

    //if (PlayersUploaded->size() > 14)
    //{
    //    columns = 14;
    //}
    //else
    //{
    //    columns = PlayersUploaded->size();
    //}

    //if (columns > 0)
    //{
    //    if (ImGui::BeginTable("tablefiles", columns*2))
    //    {
    //        for (int i = 0; i < columns ; i++)
    //        {
    //            ImGui::TableSetupColumn("", ImGuiTableColumnFlags_WidthFixed, FileImage.width);
    //            ImGui::TableSetupColumn("", ImGuiTableColumnFlags_WidthFixed, 40.0f);
    //        }
    //        //ImGui::TableHeadersRow();
    //        ImGui::TableNextRow();
    //        ImGui::TableSetColumnIndex(0);
    //        for (const auto& player : *PlayersUploaded)
    //        {
    //            if (ImGui::ImageButton(player->GetName().c_str(), (void*)(intptr_t)FileImage.FileTextureID, ImVec2(FileImage.width, FileImage.height)))
    //            {
    //                ContentsVisibility = true;
    //            }
    //            //ImGui::TableNextColumn();
    //            ImGui::Spacing();
    //            ImGui::Spacing();
    //            ImGui::Text(player->GetName().c_str());

    //            ImGui::TableNextColumn();

    //        }
    //        ImGui::EndTable();
    //    }
    //}
    //else
    //{
    //    ImGui::TextWrapped("No players have been loaded");
    //}

    if (ContentsVisibility)
    {
        ImGui::TextWrapped("Player %s was loaded", FileToUse.c_str());
    }

    ImGui::End();
}

void PlayersLoaded::SetPlayersUploaded(std::vector<std::shared_ptr<Player>>* players)
{
    PlayersUploaded = players;
}

void PlayersLoaded::SetCurrentPlayer(std::shared_ptr<Player> player)
{
    if (player != NULL)
    {
        CurrentPlayer = player;

    }
}

std::shared_ptr<Player> PlayersLoaded::GetCurrentPlayer()
{
    return CurrentPlayer;
}
