#pragma once
#include "UIPanel.h"
#include "Player.h"
#include "File.h"

class PlayerUploadFile;
class PlayerUploadText;

class FileUploader : public UIPanel
{
public:
    FileUploader(const bool& noMove, const bool& noResize, const bool& noCollapse, const std::string& name, const bool& visible);

    std::shared_ptr<Player> GetPlayerUploaded();

    void RenderPanel() override;

    void SetFileState(const FileUploadState& file);
    FileUploadState GetFileState();
protected:
    std::shared_ptr<Player> PlayerUploaded;
    FileUploadState FileState;

    std::shared_ptr<PlayerUploadText> TextInsertPanel;
    std::shared_ptr<PlayerUploadFile> FileInsertPanel;


};

