#include "PlayerUploadFile.h"
#include "Player.h"

void PlayerUploadFile::RenderFileDragAndDrop(std::shared_ptr<Player>& ActivePlayer, FileUploadState& fileState)
{
	if (fileState.isDragging)
    {
		ImGui::Text("Drop file here: ");
		if (*fileState.filePath != ' ')
		{
			// check to see if cursor was inside this panel
			ImVec2 panelPos = ImGui::GetCursorScreenPos();
			ImVec2 panelSize = ImGui::GetContentRegionAvail();

			if (ImGui::IsMouseHoveringRect(panelPos, ImVec2(panelPos.x + panelSize.x, panelPos.y + panelSize.y)))
			{
				ImGui::Text(fileState.filePath);
				std::shared_ptr<Player> NewPlayer = std::make_shared<Player>();
                if (NewPlayer->ReadAttributesFromFile(fileState.filePath))
                {
                    ActivePlayer = NewPlayer;
                    fileState.isDragging = false;
                }
                else
                {
                    fileState.isDragging = false;

		            //ImGui::TextWrapped("File could not be loaded, it does not contain data about a FM Player or is not in the right format. Please input a valid file");
                    ValidFile = false;
                }
			}
			else
			{
				const char  empty = ' ';
				strncpy(fileState.filePath, &empty, 1);
			}
		}
	}
	else if(ActivePlayer != NULL)
    {
        ImGui::Text("Drop file here to change player loaded ");
	}
    else if (!ValidFile)
    {
        ImGui::TextWrapped("File could not be loaded, it does not contain data about a FM Player or is not in the right format. Please input a valid file");

    }
    else
    {
        ImGui::Text("Drag file here: ");
    }
}
