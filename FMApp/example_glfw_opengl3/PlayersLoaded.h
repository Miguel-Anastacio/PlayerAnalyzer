#pragma once
#include "ImagesPanel.h"

class Player;
class PlayersLoaded : public ImagesPanel
{
public:

    PlayersLoaded(const bool& noMove, const bool& noResize, const bool& noCollapse, const std::string& name, const bool& visible, const Image& image);
    void RenderPanel() override;

    void SetPlayersUploaded(std::vector<std::shared_ptr<Player>>* players);
    void SetCurrentPlayer(std::shared_ptr<Player> player);
    std::shared_ptr<Player> GetCurrentPlayer();
private:
    std::vector<std::shared_ptr<Player>>* PlayersUploaded;

    std::shared_ptr<Player>CurrentPlayer;

    
  
};

