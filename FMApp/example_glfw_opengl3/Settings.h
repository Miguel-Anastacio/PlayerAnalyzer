#pragma once
#include "UIPanel.h"
#include <memory>

enum class TreeNodeSelected
{
    None = 0,
    Attributes,
    Efficiency,
    Weights
};

class Settings : public UIPanel
{
public:
    Settings(const bool& noMove, const bool& noResize, const bool& noCollapse, const std::string& name, const bool& visible);
    //~Settings();
    void RenderPanel() override;

    void SetHighlightRefs(std::shared_ptr<Highlight<int>> attHigh, std::shared_ptr<Highlight<float>> effHigh, std::shared_ptr<Highlight<float>> weightHigh);

protected:
    template <typename T>
    void RenderColorCodeEdit(Highlight<T>& highlight, const TreeNodeSelected& node)
    {
        ImGui::PushID("Index");
        int i = 0;
        char buffer[20];   // A buffer to store the resulting string
        for (auto& codes : highlight.ColorCodes)
        {
            // Using sprintf to convert int to char*
            sprintf(buffer, "%d", i);

            // The buffer now contains the integer as a C-style string
            char* charPointer = buffer;
            if (ImGui::ColorButton(charPointer, codes.Color))
            {
                NodeSelected = node;
                ColorToEdit = &codes.Color;
            }
            ImGui::SameLine();
            //ImGui::PushFont(font);
            if constexpr (std::is_same_v<T, int>)
            {
                ImGui::Text("%d - %d ", codes.MinValue, codes.MaxValue);
            }
            else if constexpr (std::is_same_v<T, float>)
            {
                ImGui::Text("%.0f - %.0f ", codes.MinValue, codes.MaxValue);
            }
            else {
                ImGui::Text("Unknown Type");
            }
            i++;
        }

        ImGui::PopID();
    }

    void RenderEditableColorButton(ImVec4& color,int id, const char* text, const TreeNodeSelected& node);
    void RenderWeightHighlighColor(Highlight<float>& highlight, const TreeNodeSelected& node);


private:

    TreeNodeSelected NodeSelected = TreeNodeSelected::None;

    std::shared_ptr<Highlight<int>> AttributesHighlight;
    std::shared_ptr<Highlight<float>> EfficiencyHighlight;
    std::shared_ptr<Highlight<float>> WeightHighlight;


    bool AttributesColorPickerVisible = false;
    bool EfficiencyColorPickerVisible = false;
    bool WeightColorPickerVisible = false;
    ImVec4* ColorToEdit = NULL;
};

