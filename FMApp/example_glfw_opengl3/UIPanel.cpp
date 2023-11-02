#include "UIPanel.h"

UIPanel::UIPanel()
{
    SetupWindowFlags(false, false, false);
}
UIPanel::UIPanel(const bool& noMove, const bool& noResize, const bool& noCollapse, const std::string& name, const bool& visible)
{
    SetupWindowFlags(noMove, noResize, noCollapse);
    Name = name;
    Visibility = visible;
}

//UIPanel::UIPanel(const bool& noMove, const bool& noResize, const bool& noCollapse, const std::string& name, const bool& visible, TextureManager& textureMgr)
//{
//}

void UIPanel::SetupWindowFlags(const bool& noMove = false, const bool& noResize = false, const bool& noCollapse = false)
{
    NoMove = noMove;
    NoResize = noResize;
    NoCollapse = noCollapse;
    if (NoMove)            window_flags |= ImGuiWindowFlags_NoMove;
    if (NoResize)          window_flags |= ImGuiWindowFlags_NoResize;
    if (NoCollapse)        window_flags |= ImGuiWindowFlags_NoCollapse;

}

void UIPanel::SetVisibility(const bool& state)
{
    Visibility = state;
}

void UIPanel::SetContentsVisibility(const bool& state)
{
    ContentsVisibility = state;
}

void UIPanel::HelpMarker(const char* desc)
{
    ImGui::TextDisabled("(?)");
    if (ImGui::BeginItemTooltip())
    {
        ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
        ImGui::TextUnformatted(desc);
        ImGui::PopTextWrapPos();
        ImGui::EndTooltip();
    }
}


void UIPanel::RenderPanel()
{
    if (Visibility)
    {
        ImGui::Begin(Name.c_str(), nullptr, window_flags);
        if (ContentsVisibility)
        {

        }
        // actual panel render here

        ImGui::End();
    }
}



