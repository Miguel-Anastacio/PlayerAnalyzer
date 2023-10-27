#pragma once
#include <imgui.h>
#include <string>
#include <vector>


template <typename T>
struct Highlight
{
    std::vector<T> threshold = { 20, 40, 60, 80, 100 };
    // defaultColors
    // red, orange, yellow, lime green, green
    std::vector<ImU32> colors = { IM_COL32(255, 0, 0, 255),
                        IM_COL32(255, 128, 0, 255),
                        IM_COL32(255, 255, 0, 190),
                        IM_COL32(128, 255, 0, 220),
                        IM_COL32(0, 255, 0, 220)
                      };

    Highlight(const std::vector<T>& t, const std::vector<ImU32>& col) : threshold(t), colors(col)
    {
    };
    Highlight(const std::vector<T>& t) : threshold(t)
    {
    };
    
    Highlight() {};

};

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
    template <typename T>
    void ColorCodeTableItems(const T& value, const Highlight<T>& highlight)
    {
        for (int i = 0; i < highlight.threshold.size(); i++)
        {
            if (value < highlight.threshold[i])
            {
                if (value == 0)
                {
                    ImGui::TableSetBgColor(ImGuiTableBgTarget_CellBg, IM_COL32(0, 0, 0, 0));
                    break;
                }

                if (i < highlight.colors.size())
                {
                    ImGui::TableSetBgColor(ImGuiTableBgTarget_CellBg, highlight.colors[i]);
                    break;
                }
            }

            // when value is outside of thershold jus give him he maximum value
            else if (i == highlight.threshold.size() - 1)
            {
                ImGui::TableSetBgColor(ImGuiTableBgTarget_CellBg, highlight.colors[i]);
                break;
            }
        }
    };

    template<typename T>
    void RenderStringValuePairTable(const std::string text, const T& value, const Highlight<T> highlight, ImFont* font)
    {
        //ImGui::Indent();
        ImGui::Text(text.c_str());
        ImGui::TableNextColumn();

        ImGui::PushFont(font);
        ColorCodeTableItems(value, highlight);
        if constexpr (std::is_same_v<T, int>)
        {
            ImGui::Text("%d", value);
        }
        else if constexpr (std::is_same_v<T, float>)
        {
            ImGui::Text("%.2f", value);
        }
        else {
            ImGui::Text("Unknown Type");
        }

        ImGui::TableNextColumn();
        ImGui::PopFont();
    }
    template<typename T>
    void RenderStringValuePairTableAsSelectable(const std::string text, const T& value, const Highlight<T> highlight, ImFont* font)
    {
        //ImGui::Indent();
        ImGui::Selectable(text.c_str());
        ImGui::TableNextColumn();

        ImGui::PushFont(font);
        ColorCodeTableItems(value, highlight);
        if constexpr (std::is_same_v<T, int>)
        {
            ImGui::Text("%d", value);
        }
        else if constexpr (std::is_same_v<T, float>)
        {
            ImGui::Text("%.2f", value);
        }
        else {
            ImGui::Text("Unknown Type");
        }

        ImGui::TableNextColumn();
        ImGui::PopFont();
    }

    bool Visibility = false;
    bool ContentsVisibility = false;

    std::string Name;
    bool NoMove;
    bool NoResize;
    bool NoCollapse;
    ImGuiWindowFlags window_flags = 0;

};

