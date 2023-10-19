#include "PlayerUploadText.h"


void PlayerUploadText::RenderFileUploadText(std::shared_ptr<Player>& player)
{
    std::shared_ptr<Player> NewPlayer;

    // Upload file name window
    ImGui::TextWrapped("Please insert file name with extension, (make sure that the file is in the same directory as the app");

    static char inputText[256] = ""; // Buffer to store the text input

    // ImGui InputText widget
    ImGui::InputText("Enter File Name", inputText, IM_ARRAYSIZE(inputText));

    // ImGui button to trigger file reading
    if (ImGui::Button("Read File"))
    {
        NewPlayer = std::make_shared<Player>();
        if (!NewPlayer->ReadAttributesFromFile(inputText))
        {
            validFile = false;
        }
        else
        {
            player = NewPlayer;
            validFile = true;
        }

        if (!validFile)
            ImGui::Text("Can't find file");
    }
}