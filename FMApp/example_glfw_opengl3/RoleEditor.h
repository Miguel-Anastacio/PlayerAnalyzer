#pragma once
#include "UIPanel.h"
#include <vector>
#include<memory>
struct Role;
struct AttributeWeight;
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
    void RenderAttributeTableMember(AttributeWeight& att, const bool& highlight = false);
    void RenderAttributeSelected(const AttributeWeight* attribute);

    std::vector<AttributeWeight> TechnicalAttributes;
    std::vector<AttributeWeight> MentalAttributes;
    std::vector<AttributeWeight> PhysicalAttributes;
    Role* CurrentRole = NULL;

    bool saveWindow = false;
    SaveRolePanel* SaveRoleScreen;

};

