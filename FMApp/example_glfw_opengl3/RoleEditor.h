#pragma once
#include "UIPanel.h"
#include <vector>
#include <memory>
#include "Define.h"
#include <unordered_map>
class SaveRolePanel;
class RoleEditor : public UIPanel
{
public:
    RoleEditor(const bool& noMove, const bool& noResize, const bool& noCollapse, const std::string& name, const bool& visible, SaveRolePanel* roleSaver);
    void RenderPanel() override;
    void SetCurrentRole(Role& role);



protected:
    void BuildAllAttributesArray();
    void RenderAllAttributes();

    bool AttributeSelectedIsInUse = false;
    AttributeWeight* AttributeSelected = NULL;
    void RenderAttributeFromVector(std::vector<AttributeWeight>& vector, int index);

    template<typename T>
    void RenderAttributeTableMember(AttributeWeight& att, const T& value, const Highlight<T>& highlight, ImFont* font)
    {
        ColorCodeTableItems(value, highlight);

        if (ImGui::Selectable(att.Name.c_str(), AttributeSelectedMap.at(att.ID)))
        {
            //if(AttributeSelected->Weight == 0)
            // deselect the previous attribute
            AttributeSelectedMap.at(PreviousAtributeSelectedID) = false;
            // set this attribute to selected
            AttributeSelectedMap.at(att.ID) = true;
            // update the previous ID
            PreviousAtributeSelectedID = att.ID;

            AttributeSelected = &att;
            AttributeSelectedIsInUse = false;
        }

        ImGui::TableNextColumn();
        ImGui::PushFont(font);
        ColorCodeTableItems(value, highlight);
        ImGui::Text("%.1f", value);
        ImGui::PopFont();
        ImGui::TableNextColumn();

    };

    void RenderAttributeSelected(const AttributeWeight* attribute);

    std::vector<AttributeWeight> TechnicalAttributes;
    std::vector<AttributeWeight> MentalAttributes;
    std::vector<AttributeWeight> PhysicalAttributes;
    Role* CurrentRole = NULL;

    bool saveWindow = false;
    SaveRolePanel* SaveRoleScreen;

    std::unordered_map<uint64_t, bool>  AttributeSelectedMap;
    uint64_t PreviousAtributeSelectedID = 0;

};

