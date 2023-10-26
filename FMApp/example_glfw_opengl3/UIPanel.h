#pragma once
#include <imgui.h>
#include <string>
class TextureManager;
class UIPanel
{
public:
    UIPanel();
    UIPanel(const bool& noMove, const bool& noResize, const bool& noCollapse, const std::string& name, const bool& visible);
    //UIPanel(const bool& noMove, const bool& noResize, const bool& noCollapse, const std::string& name, const bool& visible, TextureManager& textureMgr);
    virtual ~UIPanel() {};

    virtual void RenderPanel();
    void SetupWindowFlags(const bool& noMove, const bool& noResize,const bool& noCollapse);

    void SetVisibility(const bool& state);
    void SetContentsVisibility(const bool& state);
protected:

    bool Visibility = false;
    bool ContentsVisibility = false;

    std::string Name;
    bool NoMove;
    bool NoResize;
    bool NoCollapse;
    ImGuiWindowFlags window_flags = 0;
};

