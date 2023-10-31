#include "PlayerAttributeComparison.h"

PlayerAttributeComparison::PlayerAttributeComparison(const bool& noMove, const bool& noResize, const bool& noCollapse, const std::string& name, const bool& visible)
    : PlayerAttributesPanel(noMove, NoResize, noCollapse, name, visible)
{

}

void PlayerAttributeComparison::RenderPanel()
{
    float start = 260;
    float tableLength = 640;
    ImGui::Begin(Name.c_str(), nullptr, window_flags);
    ImGui::Separator();
    ImGui::Indent(start);
    ImGui::Text("Player 1");
    ImGui::SameLine(start, tableLength);
    ImGui::Text("Player 2");
    ImGui::Unindent(start);
    ImGui::Separator();
    ImGui::Spacing();
    ImGui::Spacing();
    ImGui::Spacing();
    RenderAttributeTable(PlayerToDisplay);
    ImGui::SameLine();
    RenderAttributeTable(SecondPlayer);
    ImGui::End();
}

void PlayerAttributeComparison::SetSecondPlayer(const std::shared_ptr<Player>& player)
{
    SecondPlayer = player;
}
