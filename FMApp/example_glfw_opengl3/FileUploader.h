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
    void ResetPlayerUploaded();
    void SetPlayerUploadedRef(std::shared_ptr<Player> pl);

    bool GetNewPlayerUploaded();

    void RenderPanel() override;

    void SetFileState(FileUploadState& file);
    FileUploadState* GetFileState();
protected:
    std::shared_ptr<Player> PlayerUploaded;
    FileUploadState* FileState;

    std::shared_ptr<PlayerUploadText> TextInsertPanel;
    std::shared_ptr<PlayerUploadFile> FileInsertPanel;

    // gets set to true when a new player is uploaded
    bool NewPlayerUploaded = false;

    uint16_t ValidPlayersUploaded = 0;

};

