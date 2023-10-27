#include "RoleEditor.h"
#include "Define.h"
#include "Database.h"
#include "SaveRolePanel.h"
RoleEditor::RoleEditor(const bool& noMove, const bool& noResize, const bool& noCollapse, const std::string& name, const bool& visible, SaveRolePanel* roleSaver)
    : UIPanel(noMove, noResize, noCollapse, name, visible)
{
    BuildAllAttributesArray();
    SaveRoleScreen = roleSaver;

}

void RoleEditor::RenderPanel()
{
    ImGui::Begin(Name.c_str(), nullptr, window_flags);
    ImGui::Text("Role Selected: ");
    if (ContentsVisibility)
    {
        ImGui::SameLine();
        ImGui::Text(CurrentRole->Name.c_str());
        ImGui::SameLine(0, 150.0f);
        ImGui::Text("Total Weight: %.2f", CurrentRole->TotalWeight);
        ImGui::SameLine(0, 150.0f);
        ImGui::Text("Avg Weight / Atribute: %.2f", CurrentRole->TotalWeight/CurrentRole->Attributes.size());

        ImGui::Separator();
        static bool bg = false;
        static ImGuiTableFlags flags = ImGuiTableFlags_Borders;
        if (bg)   flags |= ImGuiTableFlags_RowBg;
        if (ImGui::BeginTable("table2", 6, flags, ImVec2(655,0)))
        {
            float headerSize = 140.0f;
            float smallHeaderSize = 60.0f;
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
            SaveRoleScreen->SetContentsVisibility(true);
            SaveRoleScreen->SetRoleToSave(CurrentRole);
        }
    }
    ImGui::End();

}

void RoleEditor::SetCurrentRole(Role& role)
{
    CurrentRole = &role;
    AttributeSelected = NULL;
    AttributeSelectedMap.at(PreviousAtributeSelectedID) = false;
}

void RoleEditor::BuildAllAttributesArray()
{

    for (auto& it : TechnicalAttributesNames)
    {
        AttributeWeight att(it, 0);
        att.Type = Technical;
        TechnicalAttributes.emplace_back(att);
        AttributeSelectedMap.emplace(att.ID, false);
    }
    for (auto& it : PhysicalAttributesNames)
    {
        AttributeWeight att(it, 0);
        att.Type = Physical;
        PhysicalAttributes.emplace_back(att);
        AttributeSelectedMap.emplace(att.ID, false);

    }
    for (auto& it : MentalAttributesNames)
    {
        AttributeWeight att(it, 0);
        att.Type = Mental;
        MentalAttributes.emplace_back(att);
        AttributeSelectedMap.emplace(att.ID, false);

    }

    // assign previous to a random attribute to prevent
    // exception on first selection
    PreviousAtributeSelectedID = MentalAttributes[0].ID;
}

void RoleEditor::RenderAllAttributes()
{

    int Column = 0;
    ImGui::TableSetColumnIndex(Column);
    AttributeWeight* temp = NULL;
 

    for (int i = 0; i < TechnicalAttributes.size(); i++)
    {
        RenderAttributeFromVector(TechnicalAttributes, i);
        RenderAttributeFromVector(MentalAttributes, i);
        RenderAttributeFromVector(PhysicalAttributes, i);
    }
}




void RoleEditor::RenderAttributeFromVector(std::vector<AttributeWeight>& vector, int index)
{

    ImGuiIO& io = ImGui::GetIO();
    auto boldFont = io.Fonts->Fonts[0];

    std::vector<float> thresholdAtt;
    for (int i = 1; i <= 5; i++)
    {
        float temp = (CurrentRole->TotalWeight / CurrentRole->Attributes.size() / 3) * i;
        thresholdAtt.push_back(temp);
    }
    Highlight<float> attHighlight(thresholdAtt);

    int AttributeIndexinRole = -1;
    if (index < vector.size())
    {
        AttributeIndexinRole = CurrentRole->GetAttributeIndex(vector[index].ID);
        // no data so just use the default
        if (AttributeIndexinRole == -1)
        {
            int a = ImGui::TableGetColumnIndex();
            RenderAttributeTableMember(vector[index], vector[index].Weight, attHighlight, boldFont);
            //RenderAttributeTableMember(vector[index]);
            //RenderStringValuePairTableAsSelectable(vector[index].Name, vector[index].Weight, attHighlight, boldFont);
        }
        else
        {
            //RenderStringValuePairTableAsSelectable(CurrentRole->Attributes[AttributeIndexinRole].Name, CurrentRole->Attributes[AttributeIndexinRole].Weight, attHighlight, boldFont);

            RenderAttributeTableMember(CurrentRole->Attributes[AttributeIndexinRole], CurrentRole->Attributes[AttributeIndexinRole].Weight, attHighlight, boldFont);
        }
    }
    else
    {
        ImGui::TableNextColumn();
        ImGui::TableNextColumn();
    }

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

    static bool bg = false;
    static ImGuiTableFlags flags = ImGuiTableFlags_Borders;
    if (bg)   flags |= ImGuiTableFlags_RowBg;

    if (ImGui::BeginTable("table2", 4, flags, ImVec2(420,0)))
    {
        float headerSize = 140.0f;
        float smallHeaderSize = 60.0f;
        ImGui::TableSetupColumn("Attribute Selected", ImGuiTableColumnFlags_WidthFixed, 160.0f);
        ImGui::TableSetupColumn("Use", ImGuiTableColumnFlags_WidthFixed, smallHeaderSize);
        ImGui::TableSetupColumn("Weight", ImGuiTableColumnFlags_WidthFixed, smallHeaderSize);
        ImGui::TableSetupColumn("New Weight", ImGuiTableColumnFlags_WidthFixed, smallHeaderSize*2);

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
            if (InputStatus)
            {
                CurrentRole->Attributes[IndexOfAttributeToUpdate].Weight = temp;
                //attribute->Weight = 0;
                CurrentRole->CalculateTotalWeight();
                CurrentRole->EditedFlag = true;
            }
        
        }
        else
        {
            if (temp > 0 && InputStatus)
            {

                CurrentRole->EditedFlag = true;
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
        CurrentRole->EditedFlag = true;

        AttributeSelected = nullptr;
    }
}
