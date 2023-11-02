#pragma once
#include <imgui.h>
#include <string>
#include <vector>
#include <memory>
template <typename T>
struct ColorCode
{
    T MaxValue;
    T MinValue;
    ImVec4 Color = ImVec4(0, 0, 0, 1.0f);

    ColorCode(const T& max, const T& min, const ImVec4& color) : MaxValue(max), MinValue(min), Color(color)
    {};

    ColorCode(const T& max, ImVec4 color) : MaxValue(max), Color(color)
    {
        MinValue = 0;
    };

    ColorCode(const T& max) : MaxValue(max)
    {
        MinValue = 0;
    };

   /* ColorCode(const T& max, const T& min) : MaxValue(max), MinValue(min)
    {
       
    }*/
    ColorCode() {};

};


template <typename T>
struct Highlight
{
    //std::vector<T> threshold = { 20, 40, 60, 80, 100 };
    //// defaultColors
    //// red, orange, yellow, lime green, green
    //std::vector<ImU32> colors = { IM_COL32(255, 0, 0, 255),
    //                    IM_COL32(255, 128, 0, 255),
    //                    IM_COL32(255, 255, 0, 190),
    //                    IM_COL32(128, 255, 0, 220),
    //                    IM_COL32(0, 255, 0, 220)
    //                  };

  

    std::vector<ColorCode<T>> ColorCodes;

    Highlight(const std::vector<T>& ranges, const std::vector<ImU32>& col)
    {
        for (int i = 0; i < ranges.size(); i++)
        {
            ColorCodes.push_back(ranges[i], col[i]);
        }
    };

    Highlight(const std::vector<T>& ranges) 
    {
        for (int i = 0; i < ranges.size(); i++)
        {
            ColorCodes.push_back(ranges[i]);
            if (i != 0)
            {
                ColorCodes[i].MinValue = ranges[i - 1];
            }
        }

        ColorCodes[0].Color = ImVec4(1.0f, 0, 0, 1.0f);
        ColorCodes[1].Color = ImVec4(1.0f, 0.5f, 0, 1.0f);
        ColorCodes[2].Color = ImVec4(1.0f, 1.0f, 0, 0.8f);
        ColorCodes[3].Color = ImVec4(1.0f, 1.0f, 0, 0.9f);
        ColorCodes[4].Color = ImVec4(0, 1.0f, 0, 0.9f);

    };


    Highlight(std::vector<ColorCode<T>> codes) : ColorCodes(codes) {};

    Highlight() {};

    void CopyColors(const std::vector<ImVec4>& color)
    {
        for (int i = 0; i < color.size(); i++)
        {
            if (i < ColorCodes.size())
            {
                ColorCodes[i].Color = color[i];
            }
        }
    }

    std::vector<ImVec4>GetColors()
    {
        std::vector<ImVec4> col;

        for (const auto& c : ColorCodes)
        {
            col.push_back(c.Color);
        }
        return col;
    }

    void UpdateLimts(const std::vector<T>& ranges)
    {
        for (int i = 0; i<ColorCodes.size(); i++)
        {
            ColorCodes[i].MaxValue = ranges[i];
            if (i != 0)
            {
                ColorCodes[i].MinValue = ranges[i - 1];
            }
        }
    }
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

    virtual void Clear() {};

protected:

    bool Visibility = false;
    bool ContentsVisibility = false;

    std::string Name;
    bool NoMove;
    bool NoResize;
    bool NoCollapse;
    ImGuiWindowFlags window_flags = 0;

    // Helper to display a little (?) mark which shows a tooltip when hovered.
    // In your own code you may want to display an actual icon if you are using a merged icon fonts (see docs/FONTS.md)
    static void HelpMarker(const char* desc);
    

    template <typename T>
    ImVec4 ColorCodeTableItems(const T& value, const Highlight<T>& highlight)
    {
        for (int i = 0; i < highlight.ColorCodes.size(); i++)
        {
            if (value < highlight.ColorCodes[i].MaxValue)
            {
                if (value == 0)
                {
                    //ImGui::TableSetBgColor(ImGuiTableBgTarget_CellBg,IM_COL32_BLACK);
                    return ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
                    break;
                }

                //ImGui::TableSetBgColor(ImGuiTableBgTarget_CellBg, ImGui::GetColorU32(highlight.ColorCodes[i].Color));
                return highlight.ColorCodes[i].Color;
                break;
            }

            // when value is outside of thershold jus give him he maximum value
            else if (i == highlight.ColorCodes.size() - 1)
            {
                //ImGui::TableSetBgColor(ImGuiTableBgTarget_CellBg, ImGui::GetColorU32(highlight.ColorCodes[i].Color));
                return highlight.ColorCodes[i].Color;
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
        ImVec4 Color = ColorCodeTableItems(value, highlight);
        if constexpr (std::is_same_v<T, int>)
        {
            //ImGui::Text("%d", value);
            ImGui::TextColored(Color,"%d", value);
        }
        else if constexpr (std::is_same_v<T, float>)
        {
            //ImGui::Text("%.2f", value);
            ImGui::TextColored(Color, "%.2f", value);
        }
        else {
            ImGui::Text("Unknown Type");
        }

        ImGui::TableNextColumn();
        ImGui::PopFont();
    }
    template<typename T>
    void RenderStringValuePairTableHiglighted(const std::string text, const T& value, const Highlight<T> highlight, ImFont* font, bool useDefault = false)
    {
        //ImGui::Indent();
        if (useDefault)
        {
            ImGui::TableSetBgColor(ImGuiTableBgTarget_CellBg, ImGui::GetColorU32(ImVec4(0.26f, 0.59f, 0.98f, 0.31f)));
        }
        ImGui::Text(text.c_str());
        ImGui::TableNextColumn();

        ImGui::PushFont(font);
        if (useDefault)
        {
            ImGui::TableSetBgColor(ImGuiTableBgTarget_CellBg, ImGui::GetColorU32(ImVec4(0.26f, 0.59f, 0.98f, 0.31f)));
        }
        ImVec4 Color = ColorCodeTableItems(value, highlight);
        if constexpr (std::is_same_v<T, int>)
        {
            //ImGui::Text("%d", value);
            ImGui::TextColored(Color, "%d", value);
        }
        else if constexpr (std::is_same_v<T, float>)
        {
            //ImGui::Text("%.2f", value);
            ImGui::TextColored(Color, "%.2f", value);
        }
        else {
            ImGui::Text("Unknown Type");
        }

        ImGui::TableNextColumn();
        ImGui::PopFont();
    }

    template<typename T>
    bool RenderStringValuePairTableAsSelectable(const std::string text, const T& value, const Highlight<T> highlight, ImFont* font)
    {
        bool selected = false;
        if (ImGui::Selectable(text.c_str()))
            selected = true;
        ImGui::TableNextColumn();

        ImGui::PushFont(font);
        ImVec4 Color = ColorCodeTableItems(value, highlight);
        if (selected)
        {
            ImGui::TableSetBgColor(ImGuiTableBgTarget_CellBg, ImGui::GetColorU32(ImVec4(0.26f, 0.59f, 0.98f, 0.31f)));
        }
        if constexpr (std::is_same_v<T, int>)
        {
             ImGui::TextColored(Color,"%d", value);
        }
        else if constexpr (std::is_same_v<T, float>)
        {
            ImGui::TextColored(Color, "%.2f", value);
        }
        else {
            ImGui::Text("Unknown Type");
        }

        ImGui::TableNextColumn();
        ImGui::PopFont();

        return selected;
    }




};

