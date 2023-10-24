#include "RoleEditor.h"
#include "Define.h"
#include "Database.h"
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
        static bool bg = false;
        static ImGuiTableFlags flags = ImGuiTableFlags_Borders;
        if (bg)   flags |= ImGuiTableFlags_RowBg;
        if (ImGui::BeginTable("table2", 6, flags))
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

        if (CurrentRole != NULL)
        {

            if (ImGui::Button("Save Role Weigths"))
            {
                saveWindow = true;

            }
            static char inputText[256] = ""; // Buffer to store the text input
            if (saveWindow)
            {

                // display save file window
                ImGui::Text("Save Role Window");

                // ImGui InputText widget
                bool status = ImGui::InputText("Enter File Name", inputText, IM_ARRAYSIZE(inputText), ImGuiInputTextFlags_EnterReturnsTrue);
                if (status)
                {
                    WriteRoleWeightsFile(*CurrentRole, inputText);
                    saveWindow = false;
                }
            }
        }
    }
    ImGui::End();

}

void RoleEditor::SetCurrentRole(Role& role)
{
    CurrentRole = &role;
    AttributeSelected = NULL;
}

void RoleEditor::BuildAllAttributesArray()
{

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
}

void RoleEditor::RenderAllAttributes()
{

    int Column = 0;
    ImGui::TableSetColumnIndex(Column);
    AttributeWeight* temp = NULL;
 
    ImGuiStyle& style = ImGui::GetStyle();
    style.Colors[ImGuiCol_Button] = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
    for (int i = 0; i < TechnicalAttributes.size(); i++)
    {
        RenderAttributeFromVector(TechnicalAttributes, i);
        RenderAttributeFromVector(MentalAttributes, i);
        RenderAttributeFromVector(PhysicalAttributes, i);
    }
    style = ImGui::GetStyle();
    style.Colors[ImGuiCol_Button] = ImVec4(0.2f, 0.4f, 0.6f, 1.0f);
}




void RoleEditor::RenderAttributeFromVector(std::vector<AttributeWeight>& vector, int index)
{
    int AttributeIndexinRole = -1;
    if (index < vector.size())
    {
        AttributeIndexinRole = CurrentRole->GetAttributeIndex(vector[index].ID);
        // no data so just use the default
        if (AttributeIndexinRole == -1)
        {
            RenderAttributeTableMember(vector[index]);
        }
        else
        {
    
            RenderAttributeTableMember(CurrentRole->Attributes[AttributeIndexinRole], true);
        }
    }
    else
    {
        ImGui::TableNextColumn();
    }

    ImGui::TableNextColumn();
}

void RoleEditor::RenderAttributeTableMember(AttributeWeight& att, const bool& highlight)
{
    if(highlight)
        ImGui::TableSetBgColor(ImGuiTableBgTarget_CellBg, IM_COL32(0, 255, 0, 30));


    if (ImGui::Button(att.Name.c_str()))
    {
        //if(AttributeSelected->Weight == 0)
        AttributeSelected = &att;
        AttributeSelectedIsInUse = false;
    }

    ImGui::TableNextColumn();
    if (highlight)
        ImGui::TableSetBgColor(ImGuiTableBgTarget_CellBg, IM_COL32(0, 255, 0, 30));
    ImGui::Text("%.1f", att.Weight);
}

void RoleEditor::RenderAttributeSelected(const AttributeWeight* attribute)
{
    if (attribute == NULL)
        return;

    ImGui::Spacing();
    ImGui::Spacing();
    ImGui::Spacing();
    ImGui::Spacing();
    ImGui::Spacing();

    // evaluate weight
    if (attribute->Weight > 0)
        AttributeSelectedIsInUse = true;
    float temp = attribute->Weight;
    bool InputStatus = false;

    if (ImGui::BeginTable("table2", 4))
    {
        float headerSize = 140.0f;
        float smallHeaderSize = 60.0f;
        ImGui::TableSetupColumn("Attribute Selected", ImGuiTableColumnFlags_WidthFixed, headerSize);
        ImGui::TableSetupColumn("Use", ImGuiTableColumnFlags_WidthFixed, smallHeaderSize);
        ImGui::TableSetupColumn("Weight", ImGuiTableColumnFlags_WidthFixed, smallHeaderSize);
        ImGui::TableSetupColumn("New Weight", ImGuiTableColumnFlags_WidthFixed, smallHeaderSize);

        ImGui::TableHeadersRow();
        ImGui::TableNextRow();
        ImGui::TableSetColumnIndex(0);

        ImGui::Text(attribute->Name.c_str());
        ImGui::TableNextColumn();
        ImGui::Checkbox("  ", &AttributeSelectedIsInUse);
        ImGui::TableNextColumn();

        ImGui::Text("%.2f",temp);
        ImGui::TableNextColumn();
        if(AttributeSelectedIsInUse)
            InputStatus = ImGui::InputFloat(" ", &temp, 0.0f, 0.0f, "%.2f", ImGuiInputTextFlags_EnterReturnsTrue);
        ImGui::EndTable();
    }

    bool isPresent = false;
    int IndexOfAttributeToUpdate = -1;
    // see if the attribute in question is already present in the role
    int i = 0;
    for (auto& att : CurrentRole->Attributes)
    {
        if (att.ID == attribute->ID)
        {
            IndexOfAttributeToUpdate = i;
            isPresent = true;
            break;
        }
        i++;
    }


    // if weight is > 0
    if (AttributeSelectedIsInUse)
    {
        if (isPresent)
        {
            if (attribute->Weight > 4)
            {
                int a = 2;
            }
  
            CurrentRole->Attributes[IndexOfAttributeToUpdate].Weight = temp;
            //attribute->Weight = 0;
            CurrentRole->CalculateTotalWeight();
        }
        else
        {
            if (temp > 0 && InputStatus)
            {

                CurrentRole->Attributes.emplace_back(attribute->Name, temp);
                AttributeSelected = NULL;
                CurrentRole->CalculateTotalWeight();

            }
        }
        
    }
    else if (!AttributeSelectedIsInUse && isPresent)
    {
        
        CurrentRole->Attributes.erase(CurrentRole->Attributes.begin() + IndexOfAttributeToUpdate);
        CurrentRole->CalculateTotalWeight();
        AttributeSelected = nullptr;
    }
}
