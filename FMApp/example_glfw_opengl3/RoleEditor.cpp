#include "RoleEditor.h"
#include "Define.h"
RoleEditor::RoleEditor(const bool& noMove, const bool& noResize, const bool& noCollapse, const std::string& name, const bool& visible)
    : UIPanel(noMove, noResize, noCollapse, name, visible)
{
    BuildAllAttributesArray();
}

void RoleEditor::RenderPanel()
{
    ImGui::Begin(Name.c_str(), nullptr, window_flags);
    ImGui::Text("Role Selected: ");
    if (ContentsVisibility)
    {
        ImGui::SameLine();
        ImGui::Text(CurrentRole->Name.c_str());
        ImGui::Separator();
        if (ImGui::BeginTable("table2", 6))
        {
            float headerSize = 140.0f;
            float smallHeaderSize = 45.0f;
            ImGui::TableSetupColumn("Technical", ImGuiTableColumnFlags_WidthFixed, headerSize);
            ImGui::TableSetupColumn("Weight", ImGuiTableColumnFlags_WidthFixed, smallHeaderSize);
            ImGui::TableSetupColumn("Mental", ImGuiTableColumnFlags_WidthFixed, headerSize);
            ImGui::TableSetupColumn("Weight", ImGuiTableColumnFlags_WidthFixed, smallHeaderSize);
            ImGui::TableSetupColumn("Physical", ImGuiTableColumnFlags_WidthFixed, headerSize);
            ImGui::TableSetupColumn("Weight", ImGuiTableColumnFlags_WidthFixed, smallHeaderSize);
            ImGui::TableHeadersRow();
            ImGui::TableNextRow();


            RenderAllAttributes();
            ImGui::EndTable();
        }

        RenderAttributeSelected(AttributeSelected);
    }
    ImGui::End();

}

void RoleEditor::SetCurrentRole(Role& role)
{
    CurrentRole = &role;
}

void RoleEditor::BuildAllAttributesArray()
{
    std::vector<AttributeWeight> TechnicalAttributes;
    std::vector<AttributeWeight> MentalAttributes;
    std::vector<AttributeWeight> PhysicalAttributes;
    for (auto& it : TechnicalAttributesNames)
    {
        AttributeWeight att(it, 0);
        att.Type = Technical;
        TechnicalAttributes.emplace_back(att);
    }
    for (auto& it : PhysicalAttributesNames)
    {
        AttributeWeight att(it, 0);
        att.Type = Physical;
        PhysicalAttributes.emplace_back(att);
    }
    for (auto& it : MentalAttributesNames)
    {
        AttributeWeight att(it, 0);
        att.Type = Mental;
        MentalAttributes.emplace_back(att);
    }

    for (int i = 0; i < TechnicalAttributes.size(); i++)
    {
        AllAttributesSorted.emplace_back(TechnicalAttributes[i]);
        AllAttributesSorted.emplace_back(MentalAttributes[i]);
        if (i < PhysicalAttributes.size())
            AllAttributesSorted.emplace_back(PhysicalAttributes[i]);
    }
}

void RoleEditor::RenderAllAttributes()
{

    int Column = 0;
    ImGui::TableSetColumnIndex(Column);
    for (auto& att : AllAttributesSorted)
    {
        bool RoleHasDataAboutThisAttribute = false;
        float weight = 0.0;
        ImGui::TableSetBgColor(ImGuiTableBgTarget_CellBg, IM_COL32(0, 0, 0, 0)); // Reset background color
        for (const auto& roleAtt : CurrentRole->Attributes)
        {
            if (att.Name == roleAtt.Name)
            {
                RoleHasDataAboutThisAttribute = true;
                weight = roleAtt.Weight;
                break;
            }
        }



        // no data so just use the default
        if (!RoleHasDataAboutThisAttribute)
        {
            ImGui::TableSetBgColor(ImGuiTableBgTarget_CellBg, IM_COL32(0, 0, 0, 0));
            //ImGui::Text("%s", att.Name.c_str());
            if (ImGui::Button((att.Name.c_str())))
            {
                //ImGui::Text("Remove Item");
                AttributeSelected = &att;
                //ImGui::EndMenu();


            }
            ImGui::TableNextColumn();
            ImGui::Text("%.1f", att.Weight);
        }
        else
        {
            ImGui::TableSetBgColor(ImGuiTableBgTarget_CellBg, IM_COL32(0, 255, 0, 255));

            if (ImGui::Button(att.Name.c_str()))
            {
                AttributeSelected = &att;
            }

            ImGui::TableNextColumn();
            ImGui::TableSetBgColor(ImGuiTableBgTarget_CellBg, IM_COL32(0, 255, 0, 255));
            ImGui::Text("%.1f", weight);

        }
        ImGui::TableNextColumn();
    }
}

void RoleEditor::RenderAttributeSelected(AttributeWeight* attribute)
{
    if (attribute == NULL)
        return;

    // evaluate weight
    if (attribute->Weight > 0)
        AttributeSelectedIsInUse = true;
  
    ImGui::Text("AttributeSelected : %-25s", attribute->Name.c_str());
    ImGui::SameLine();
    if (ImGui::Checkbox("Use", &AttributeSelectedIsInUse))
    {

    }
    ImGui::SameLine();
    ImGui::Text("%.2f", attribute->Weight);
    ImGui::SameLine();
    ImGui::InputFloat("New Weight", &attribute->Weight);

    // if weight is > 0
    if (attribute->Weight > 0 && AttributeSelectedIsInUse)
    {
        bool isPresent = false;
        // check if it is present in the current role
        for (auto& att : CurrentRole->Attributes)
        {
            if (att.Name == attribute->Name)
            {
                att.Weight = attribute->Weight;
                isPresent = true;
                break;
            }
        }
        if (!isPresent)
        {
            CurrentRole->Attributes.push_back(*attribute);
     
        }
    }
  
}
