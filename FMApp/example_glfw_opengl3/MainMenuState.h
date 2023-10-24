#pragma once
#include "State.h"
#include <string>
#include <memory>
class FileUploader;
class PlayerAttributesPanel;
class RoleEfficiencyPanel;
class Player;

class MainMenuState : public State
{
public:
    MainMenuState(FileUploader* fUp, PlayerAttributesPanel* att, RoleEfficiencyPanel* roleEff);

    FileUploader* fileUploader;
    PlayerAttributesPanel* attributesPanel;
    RoleEfficiencyPanel* roleEfficiencyPanel;

    void Execute(const std::vector<Role>& allRoles) override;
   
protected:

    int IsPlayerAlreadyLoaded(const std::string& name);

    std::vector<std::shared_ptr<Player>> AllPlayersLoaded;
    std::shared_ptr<Player> ActivePlayer;
};

