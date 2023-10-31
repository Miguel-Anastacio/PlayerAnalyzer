#include "Settings.h"

Settings::Settings(const bool& noMove, const bool& noResize, const bool& noCollapse, const std::string& name, const bool& visible)
    : UIPanel(noMove, noResize, noCollapse, name, visible)
{
    //const std::vector<int> ranges = { 4, 8, 12, 16, 20 };
    //AttributesHighligth = std::make_shared<Highlight<int>>(ranges);
}

//Settings::~Settings()
//{
//    // save the highlight
//    nlohmann::json  data;
//    data["Highlight"] = "Attribute";
//    data["Ranges"] = {AttributesHighlight->ColorCodes[0].MaxValue, AttributesHighlight->ColorCodes[0].MaxValue }
//}

void Settings::RenderPanel()
{
    ImGui::Begin(Name.c_str(), nullptr, window_flags);
    static float colorPickerSize = 225.0f;
    static ImVec4 color = ImVec4(114.0f / 255.0f, 144.0f / 255.0f, 154.0f / 255.0f, 200.0f / 255.0f);

    if (ImGui::TreeNode("Attributes"))
    {
        TreeNodeSelected node = TreeNodeSelected::Attributes;
        RenderColorCodeEdit(*AttributesHighlight, node);
        if(ColorToEdit != NULL)
            color = *ColorToEdit;

        if (NodeSelected == TreeNodeSelected::Attributes)
        {
            ImGui::SetNextItemWidth(colorPickerSize);
            ImGui::ColorPicker4("##picker", (float*)&color, ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoSmallPreview );
            *ColorToEdit = color;
        }
        ImGui::Spacing();
        ImGui::Spacing();
        ImGui::Spacing();
        if (ImGui::Button("Apply color scheme to all"))
        {
            EfficiencyHighlight->CopyColors(AttributesHighlight->GetColors());
            WeightHighlight->CopyColors(AttributesHighlight->GetColors());
        }

        ImGui::TreePop();
    }

    if (ImGui::TreeNode("Role Efficiency"))
    {
        TreeNodeSelected node = TreeNodeSelected::Efficiency;
        RenderColorCodeEdit(*EfficiencyHighlight, node);
        if (ColorToEdit != NULL)
            color = *ColorToEdit;

        if (NodeSelected == TreeNodeSelected::Efficiency)
        {
            ImGui::SetNextItemWidth(colorPickerSize);
            ImGui::ColorPicker4("##picker", (float*)&color, ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoSmallPreview | ImGuiColorEditFlags_NoInputs);
            *ColorToEdit = color;
        }

        ImGui::Spacing();
        ImGui::Spacing();
        ImGui::Spacing();

        if (ImGui::Button("Apply color scheme to all"))
        {
            AttributesHighlight->CopyColors(EfficiencyHighlight->GetColors());
            WeightHighlight->CopyColors(EfficiencyHighlight->GetColors());
        }
        ImGui::TreePop();
    }
    if (ImGui::TreeNode("Weights"))
    {
        TreeNodeSelected node = TreeNodeSelected::Weights;
        RenderWeightHighlighColor(*WeightHighlight,node);
        if (ColorToEdit != NULL)
            color = *ColorToEdit;

        if (NodeSelected == TreeNodeSelected::Weights)
        {
            ImGui::SetNextItemWidth(colorPickerSize);
            ImGui::ColorPicker4("##picker", (float*)&color, ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoSmallPreview | ImGuiColorEditFlags_NoInputs);
            *ColorToEdit = color;
        }
        ImGui::Spacing();
        ImGui::Spacing();
        ImGui::Spacing();

        if (ImGui::Button("Apply color scheme to all"))
        {
            AttributesHighlight->CopyColors(WeightHighlight->GetColors());
            EfficiencyHighlight->CopyColors(WeightHighlight->GetColors());
        }
        ImGui::TreePop();
    }



    ImGui::End();
}

void Settings::SetHighlightRefs(std::shared_ptr<Highlight<int>> attHigh, std::shared_ptr<Highlight<float>> effHigh, std::shared_ptr<Highlight<float>> weightHigh)
{
    AttributesHighlight = attHigh;
    EfficiencyHighlight = effHigh;
    WeightHighlight = weightHigh;
}

void Settings::RenderEditableColorButton(ImVec4& color, int id, const char* text, const TreeNodeSelected& node)
{
    char buffer[20];
    // Using sprintf to convert int to char*
    sprintf(buffer, "%d", id);

    // The buffer now contains the integer as a C-style string
    char* charPointer = buffer;
    if (ImGui::ColorButton(charPointer, color))
    {
        NodeSelected = node;
        ColorToEdit = &color;
    }
    ImGui::SameLine();
    ImGui::Text(text);

}

void Settings::RenderWeightHighlighColor(Highlight<float>& highlight, const TreeNodeSelected& node)
{
    ImGui::PushID("Index");
    
    RenderEditableColorButton(highlight.ColorCodes[0].Color, 0, "Very below average", node);
    RenderEditableColorButton(highlight.ColorCodes[1].Color, 1, "Below average", node);
    RenderEditableColorButton(highlight.ColorCodes[2].Color, 2, "Average", node);
    RenderEditableColorButton(highlight.ColorCodes[3].Color, 3, "Above average", node);
    RenderEditableColorButton(highlight.ColorCodes[4].Color, 4, "Very above average", node);

    ImGui::PopID();
}
