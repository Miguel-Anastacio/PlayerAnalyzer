#pragma once
#include "ImagesPanel.h"

class Player;
class PlayersLoaded : public ImagesPanel
{
public:

    PlayersLoaded(const bool& noMove, const bool& noResize, const bool& noCollapse, const std::string& name, const bool& visible, const Image& image);
    void RenderPanel() override;

    void SetPlayersUploaded(std::vector<Player>* players);
    void SetCurrentPlayer(Player* player);
    Player* GetCurrentPlayer();
private:
    
    std::vector<Player>* PlayersUploaded;

    Player* CurrentPlayer = NULL;
    
  
};

