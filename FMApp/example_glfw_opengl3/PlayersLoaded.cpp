#include "PlayersLoaded.h"
#include "Player.h"
PlayersLoaded::PlayersLoaded(const bool& noMove, const bool& noResize, const bool& noCollapse, const std::string& name, const bool& visible, const Image& image)
    : ImagesPanel(noMove, noResize, noCollapse, name, visible, image)
{
    FileImage.width = FileImage.width * 0.075;
    FileImage.height = FileImage.height * 0.05;

    if (true)    window_flags |= ImGuiWindowFlags_NoFocusOnAppearing;
}

void PlayersLoaded::RenderPanel()
{
    ImGui::Begin(Name.c_str(), nullptr, window_flags);
    int columns = 0;
    if (PlayersUploaded->size() == 0)
    {
        ImGui::TextWrapped("No Players have been loaded. Please use the file uploader to load player data to the app");
        ImGui::End();
        return;
    }

    if (ImGui::IsWindowFocused())
    {

        for (auto& player : *PlayersUploaded)
        {
            ImGui::PushID(player->GetUniqueID());

            ImVec2 size = ImGui::CalcTextSize(player->GetName().c_str());
            size.x = size.x + FileImage.width;
            if (size.x < 200)
                size.x = ImGui::GetContentRegionMax().x;
            size.y = FileImage.height + 5;
            if (ImGui::Selectable(player->GetName().c_str(), ContentsVisibility, 0, size))
            {
                ContentsVisibility = true;
                FileToUse = player->GetName();
                CurrentPlayer = player;
            }


            ImGui::SetItemTooltip("Press to load");
            ImGui::SameLine(ImGui::CalcTextSize(player->GetName().c_str()).x + 15.0f);

            if (ImGui::ImageButton("Image Button", (void*)(intptr_t)FileImage.FileTextureID, ImVec2(FileImage.width, FileImage.height)))
            {
                ContentsVisibility = true;
                FileToUse = player->GetName();
                CurrentPlayer = player;
            }
            ImGui::SetItemTooltip("Press to load");
            ImGui::PopID();


            //ImGui::Text(player->GetName().c_str());
        }

        if (ContentsVisibility)
        {
            ImGui::TextWrapped("Player %s was loaded", FileToUse.c_str());
        }
    }
    else
    {
        ContentsVisibility = false;
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
