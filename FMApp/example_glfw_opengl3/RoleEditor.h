#pragma once
#include "UIPanel.h"
#include <vector>
#include<memory>
struct Role;
struct AttributeWeight;

class RoleEditor : public UIPanel
{
public:
    RoleEditor(const bool& noMove, const bool& noResize, const bool& noCollapse, const std::string& name, const bool& visible);
    void RenderPanel() override;
    void SetCurrentRole(Role& role);
protected:
    void BuildAllAttributesArray();
    void RenderAllAttributes();

    bool AttributeSelectedIsInUse = false;
    AttributeWeight* AttributeSelected = NULL;
    void RenderAttributeSelected(AttributeWeight* attribute);

    std::vector<AttributeWeight> AllAttributesSorted;
    Role* CurrentRole = NULL;
};

