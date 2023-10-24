#include "MainMenuState.h"
#include "FileUploader.h"
#include "RoleEfficiencyPanel.h"
#include "PlayerAttributesPanel.h"
#include "glfw_callbacks.hpp"
#include "Player.h"
MainMenuState::MainMenuState(FileUploader* fUp, PlayerAttributesPanel* att, RoleEfficiencyPanel* roleEff)
{
    fileUploader = fUp;
    attributesPanel = att;
    roleEfficiencyPanel = roleEff;
}

void MainMenuState::Execute(const std::vector<Role>& allRoles)
{
    fileUploader->SetFileState(Callback::fileUploadState);
    fileUploader->RenderPanel();
    Callback::fileUploadState = fileUploader->GetFileState();
    //AppInterface::RenderFileUploader(ActivePlayer, Callback::fileUploadState);
    ActivePlayer = fileUploader->GetPlayerUploaded();
    if (ActivePlayer != nullptr)
    {
        int index = IsPlayerAlreadyLoaded(ActivePlayer->GetName());
        if (index != -1)
        {
            ActivePlayer = AllPlayersLoaded[index];
            ActivePlayer->UpdateEfficiency(allRoles);
        }
        else
        {
            AllPlayersLoaded.emplace_back(ActivePlayer);
            ActivePlayer->CalculateEfficiencyAllRoles(allRoles);
        }
    }


    attributesPanel->SetPlayerToDisplay(ActivePlayer);
    attributesPanel->RenderPanel();
    //AppInterface::RenderPlayerAttributes(ActivePlayer);

    roleEfficiencyPanel->SetPlayerToDisplay(ActivePlayer);
    roleEfficiencyPanel->RenderPanel();
}

int MainMenuState::IsPlayerAlreadyLoaded(const std::string& name)
{
    int i = 0;
    for (auto& it : AllPlayersLoaded)
    {

        if (name == it->GetName())
        {
            return i;
        }
        i++;
    }

    return -1;
}
