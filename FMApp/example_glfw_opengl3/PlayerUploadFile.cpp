#include "PlayerUploadFile.h"
#include "Player.h"

std::vector<Player> PlayerUploadFile::RenderFileDragAndDrop(std::shared_ptr<Player>& ActivePlayer, FileUploadState& fileState)
{
    std::vector<Player> players;
	if (fileState.isDragging)
    {
		ImGui::TextWrapped("Drop files here: ");
		for (const auto file : fileState.filePaths)
		{
			// check to see if cursor was inside this panel
			ImVec2 panelPos = ImGui::GetCursorScreenPos();
			ImVec2 panelSize = ImGui::GetContentRegionAvail();

			if (ImGui::IsMouseHoveringRect(panelPos, ImVec2(panelPos.x + panelSize.x, panelPos.y + panelSize.y)))
			{
				//ImGui::Text(file.c_str());
                Player NewPlayer;
                if (NewPlayer.ReadAttributesFromFile(file))
                {
                    players.emplace_back(NewPlayer);
                    //*ActivePlayer = NewPlayer;
                    fileState.isDragging = false;
                }
                else
                {
                    fileState.isDragging = false;
                    ValidFile = false;
                }
			}
			else
			{
				const char  empty = ' ';
				strncpy_s(fileState.filePath, &empty, 1);
			}
		}
	}
	else if(ActivePlayer != NULL)
    {
        ImGui::Text("Drop file here to change player loaded ");
	}
    else 
    {
        ImGui::TextWrapped("Drag files here (you can drag multiple):");
    }

    if (!ValidFile)
    {
        ImGui::TextWrapped("File could not be loaded, it does not contain data about a FM Player or is not in the right format. Please input a valid file");
    }

    return players;
}
