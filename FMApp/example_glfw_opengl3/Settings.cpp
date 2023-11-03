#pragma once
#include "Settings.h"
#include <fstream>
#include <istream>
#include <iostream>
Settings::Settings(const bool& noMove, const bool& noResize, const bool& noCollapse, const std::string& name, const bool& visible)
    : UIPanel(noMove, noResize, noCollapse, name, visible)
{
    //const std::vector<int> ranges = { 4, 8, 12, 16, 20 };
    //AttributesHighligth = std::make_shared<Highlight<int>>(ranges);
}

Settings::~Settings()
{
    // save the higlight
    std::ofstream file;
    file.open("settings.txt", std::ios::out);

    if (file.is_open())
    {
        WriteHighlightToFile(*AttributesHighlight, "Attributes", file);
        WriteHighlightToFile(*EfficiencyHighlight, "Efficiency", file);
        WriteHighlightToFile(*WeightHighlight, "Weights", file);
        file.close();
    }

}

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

    ReadFromSettingsFile();
}

void Settings::RenderEditableColorButton(ImVec4& color, int id, const char* text, const TreeNodeSelected& node)
{
    char buffer[20];
    // Using sprintf to convert int to char*
    sprintf_s(buffer, "%d", id);

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

void Settings::ReadFromSettingsFile()
{
    std::ifstream file("settings.txt");
    if (file.is_open())
    {
        std::string line;
        while (std::getline(file, line))
        {
            // check if line contains an ID
            if (line.find("Attributes") != std::string::npos)
            {
                for (auto& colorCodes : AttributesHighlight->ColorCodes)
                {
                    std::getline(file, line);
                    ReadDataSaveToVariable(colorCodes.MinValue, line);
                    std::getline(file, line);
                    ReadDataSaveToVariable(colorCodes.MaxValue,line);
                    std::getline(file, line);
                    ReadDataSaveToVariable(colorCodes.Color.x,line);
                    std::getline(file, line);
                    ReadDataSaveToVariable(colorCodes.Color.y,line);
                    std::getline(file, line);
                    ReadDataSaveToVariable(colorCodes.Color.z,line);
                    std::getline(file, line);
                    ReadDataSaveToVariable(colorCodes.Color.w,line);
                }          
            }
            if (line.find("Efficiency") != std::string::npos)
            {
                for (auto& colorCodes : EfficiencyHighlight->ColorCodes)
                {
                    std::getline(file, line);
                    ReadDataSaveToVariable(colorCodes.MinValue, line);
                    std::getline(file, line);
                    ReadDataSaveToVariable(colorCodes.MaxValue, line);
                    std::getline(file, line);
                    ReadDataSaveToVariable(colorCodes.Color.x, line);
                    std::getline(file, line);
                    ReadDataSaveToVariable(colorCodes.Color.y, line);
                    std::getline(file, line);
                    ReadDataSaveToVariable(colorCodes.Color.z, line);
                    std::getline(file, line);
                    ReadDataSaveToVariable(colorCodes.Color.w, line);
                }
            }
            if (line.find("Weights") != std::string::npos)
            {
                for (auto& colorCodes : WeightHighlight->ColorCodes)
                {
                    std::getline(file, line);
                    ReadDataSaveToVariable(colorCodes.MinValue, line);
                    std::getline(file, line);
                    ReadDataSaveToVariable(colorCodes.MaxValue, line);
                    std::getline(file, line);
                    ReadDataSaveToVariable(colorCodes.Color.x, line);
                    std::getline(file, line);
                    ReadDataSaveToVariable(colorCodes.Color.y, line);
                    std::getline(file, line);
                    ReadDataSaveToVariable(colorCodes.Color.z, line);
                    std::getline(file, line);
                    ReadDataSaveToVariable(colorCodes.Color.w, line);
                }
            }
        }

        file.close();
    }

}

void Settings::ReadDataSaveToVariable(float& variable, std::string&  line)
{
    try {
        variable = std::stof(line);
    }
    catch (std::invalid_argument const& ex) {
        std::cerr << "Invalid argument: " << ex.what() << std::endl;
    }
    catch (std::out_of_range const& ex) {
        std::cerr << "Out of range: " << ex.what() << std::endl;
    }
}

void Settings::ReadDataSaveToVariable(int& variable, std::string& line)
{
    try {
        variable = std::stoi(line);
    }
    catch (std::invalid_argument const& ex) {
        std::cerr << "Invalid argument: " << ex.what() << std::endl;
    }
    catch (std::out_of_range const& ex) {
        std::cerr << "Out of range: " << ex.what() << std::endl;
    }
}
