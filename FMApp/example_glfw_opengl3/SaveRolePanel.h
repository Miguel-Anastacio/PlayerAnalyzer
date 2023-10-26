#pragma once
#include "ImagesPanel.h"
#include <filesystem>
struct Role;
class SaveRolePanel : public ImagesPanel
{
   const Role* RoleToSave;
   bool FeedbackVisibleTab1 = false;
   bool FeedbackVisibleTab2 = false;
   std::string FileNameSaved;

   std::string FileToUse;
public:
    SaveRolePanel(const bool& noMove, const bool& noResize, const bool& noCollapse, const std::string& name, const bool& visible, const Image& image);
    void RenderPanel() override;

    void RenderFeedback(const std::string& text, const bool& visibility);
    void SetRoleToSave(const Role* role);
};

