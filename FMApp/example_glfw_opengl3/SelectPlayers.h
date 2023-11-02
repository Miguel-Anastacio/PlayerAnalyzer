#pragma once
#include "ImagesPanel.h"
#include <unordered_map>
class Player;
class PlayerAttributeComparison;
class SelectPlayers : public ImagesPanel
{
public:
    SelectPlayers(const bool& noMove, const bool& noResize, const bool& noCollapse, const std::string& name, const bool& visible, const Image& image);

    void RenderPanel() override;
    void SetPlayersUploaded(std::vector<std::shared_ptr<Player>>* players);

    void SetAttributeComparisonRef(PlayerAttributeComparison* ref);

    void UpdatePlayersSelectedMap();
private:
    std::vector<std::shared_ptr<Player>>* PlayersUploaded;

    std::unordered_map<uint64_t, bool>PlayersSelectedMap;
    std::vector<int> PlayersSelectedIndex;
    PlayerAttributeComparison* AttributeComparison = NULL;
};

