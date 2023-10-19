#include "Player.h"
#include <imgui.h>
#include "File.h"
namespace AppInterface
{
    bool compareStructs(const AttributeWeight& a, const AttributeWeight& b) {
        return a.Type < b.Type;  // Sort by id in ascending order
    }
    std::vector<AttributeWeight> AllAttributesSorted;
    bool AttributesDisplayed = false;

    void SetupEmptyAttributes()
    {
        std::vector<AttributeWeight> TechnicalAttributes;
        std::vector<AttributeWeight> MentalAttributes;
        std::vector<AttributeWeight> PhysicalAttributes;
        for (auto& it : TechnicalAttributesNames)
        {
            AttributeWeight att(it, 0);
            att.Type = Technical;
            TechnicalAttributes.emplace_back(att);
        }
        for (auto& it : PhysicalAttributesNames)
        {
            AttributeWeight att(it, 0);
            att.Type = Physical;
            PhysicalAttributes.emplace_back(att);
        }
        for (auto& it : MentalAttributesNames)
        {
            AttributeWeight att(it, 0);
            att.Type = Mental;
            MentalAttributes.emplace_back(att);
        }

        for (int i = 0; i < TechnicalAttributes.size(); i++)
        {
            AllAttributesSorted.emplace_back(TechnicalAttributes[i]);
            AllAttributesSorted.emplace_back(MentalAttributes[i]);
            if(i < PhysicalAttributes.size())
                AllAttributesSorted.emplace_back(PhysicalAttributes[i]);
        }

    }

    void RenderTextWithBackground(const std::string& text, ImU32 backgroundColor) {
        // Get the current ImGui window
     

        // Get the position where you want to draw the text
        ImVec2 textPos = ImGui::GetCursorPos();

        // Get the size of the text
        ImVec2 textSize = ImGui::CalcTextSize(text.c_str());

        // Draw the background
        ImGui::GetWindowDrawList()->AddRectFilled(textPos, ImVec2(textPos.x + textSize.x, textPos.y + textSize.y), backgroundColor);

        // Draw the text on top of the background
        ImGui::Text(text.c_str());
    }


    void RenderFileInsertText(std::shared_ptr<Player>& ActivePlayer)
	{
        // keep track if valid file was uploaded
        bool validFile = true;
        std::shared_ptr<Player> NewPlayer;
        // setup flags for file uploading window
        static bool no_move = false;
        static bool no_resize = false;
        static bool no_collapse = true;

        ImGuiWindowFlags window_flags = 0;

        if (no_move)            window_flags |= ImGuiWindowFlags_NoMove;
        if (no_resize)          window_flags |= ImGuiWindowFlags_NoResize;
        if (no_collapse)        window_flags |= ImGuiWindowFlags_NoCollapse;

        // Upload file name window
        ImGui::TextWrapped("Please insert file name with extension, (make sure that the file is in the same directory as the app");

        static char inputText[256] = ""; // Buffer to store the text input

        // ImGui InputText widget
        ImGui::InputText("Enter File Name", inputText, IM_ARRAYSIZE(inputText));

        // ImGui button to trigger file reading
        if (ImGui::Button("Read File"))
        {
            /*
            ActivePlayer->ClearAttributes();
            // Call your function to read the file based on the entered filename
            if (ActivePlayer->ReadAttributesFromFile(inputText))
            {
                //ImGui::CloseCurrentPopup();

            }*/

            // actual implementation
            NewPlayer = std::make_shared<Player>();
            if (!NewPlayer->ReadAttributesFromFile(inputText))
            {
                validFile = false;

            }
            else
            {
                ActivePlayer = NewPlayer;
                validFile = true;
                
            }

            if (!validFile)
                ImGui::Text("Can't find file");

        }

	}

    void RenderFileDragAndDrop(std::shared_ptr<Player>& ActivePlayer, FileUploadState& fileState)
    {
        bool validFile = true;
        if (fileState.isDragging) {
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
                    if (!NewPlayer->ReadAttributesFromFile(fileState.filePath))
                    {
                        validFile = false;
                    }
                    else
                    {
                        ActivePlayer = NewPlayer;
                        validFile = true;
                    }

                    if (!validFile)
                        ImGui::Text("Can't find file");
                }
                else
                {
                    const char  empty = ' ';
                    strncpy(fileState.filePath, &empty, 1);
                }
            }
        }
        else {
            ImGui::Text("Drag a file here!");
        }
    }

    void RenderFileUploader(std::shared_ptr<Player>& ActivePlayer, FileUploadState& fileState)
    {

        // setup flags for file uploading window
        static bool no_move = false;
        static bool no_resize = false;
        static bool no_collapse = true;

        ImGuiWindowFlags window_flags = 0;

        if (no_move)            window_flags |= ImGuiWindowFlags_NoMove;
        if (no_resize)          window_flags |= ImGuiWindowFlags_NoResize;
        if (no_collapse)        window_flags |= ImGuiWindowFlags_NoCollapse;
        ImGui::Begin("File Uploader", nullptr, window_flags);
 
        ImGuiTabBarFlags tab_bar_flags = ImGuiTabBarFlags_None;
        if (ImGui::BeginTabBar("MyTabBar", tab_bar_flags))
        {
            if (ImGui::BeginTabItem("Insert File Name"))
            {
                RenderFileInsertText(ActivePlayer);
                ImGui::EndTabItem();
            }
            if (ImGui::BeginTabItem("Drag and Drop File"))
            {
                RenderFileDragAndDrop(ActivePlayer, fileState);
                ImGui::EndTabItem();
            }
            // to do
            if (ImGui::BeginTabItem("Paste Image"))
            {
                ImGui::Text("This is the Cucumber tab!\nblah blah blah blah blah");
                ImGui::EndTabItem();
            }
            ImGui::EndTabBar();
        }

        ImGui::End();

    }

    void RenderPlayerAttributes(const std::shared_ptr<Player>& player)
    {
        //// setup flags for file uploading window

        static bool no_move = true;
        static bool no_resize = true;
        static bool no_collapse = true;

        ImGuiWindowFlags window_flags = 0;

        no_move = false;
        no_resize = false;
        no_collapse = false;
        if (no_move)            window_flags |= ImGuiWindowFlags_NoMove;
        if (no_resize)          window_flags |= ImGuiWindowFlags_NoResize;
        if (no_collapse)        window_flags |= ImGuiWindowFlags_NoCollapse;

        ImGui::Begin("Player Attributes", nullptr, window_flags);

        if (player != nullptr)
        {
            std::vector<Attribute> PlayerAttributes = player->GetPlayerAttributes();

            static bool bg = true;
            static ImGuiTableFlags flags = ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg;
            if (bg)   flags |= ImGuiTableFlags_Borders;
            // [Method 2] Using TableNextColumn() called multiple times, instead of using a for loop + TableSetColumnIndex().
            // This is generally more convenient when you have code manually submitting the contents of each columns.
            if (PlayerAttributes.size() > 0)
            {
                if (ImGui::BeginTable("table2", 3, flags))
                {
                    int attributesIndex = 0;
                    float headerSize = 160.0f;
                    ImGui::TableSetupColumn("Technical", ImGuiTableColumnFlags_WidthFixed, headerSize);
                    ImGui::TableSetupColumn("Mental", ImGuiTableColumnFlags_WidthFixed, headerSize);
                    ImGui::TableSetupColumn("Physical", ImGuiTableColumnFlags_WidthFixed, headerSize);
                    ImGui::TableHeadersRow();
                    ImGui::TableNextRow();

                    for (int column = 0; column < 3; column++)
                    {
                        // Fill the first column first
                        for (int i = 0; i < 14; ++i)
                        {
                            //ImGui::TableNextRow();
                            ImGui::TableSetColumnIndex(column);
                            if (attributesIndex >= PlayerAttributes.size())
                                break;
                            ImGui::Text("%-20s %d", PlayerAttributes[attributesIndex].Name.c_str(), PlayerAttributes[attributesIndex].Value);
                            attributesIndex++;
                        }
                    }

                    ImGui::EndTable();
                }
            }
        }
        ImGui::End();
    }

    void RenderRoleEfficiency(const std::shared_ptr<Player>& player)
    {
        //// setup flags for file uploading window
        static bool no_move = true;
        static bool no_resize = true;
        static bool no_collapse = true;
        ImGuiWindowFlags window_flags = 0;

        no_move = false;
        no_resize = false;
        no_collapse = false;
        if (no_move)            window_flags |= ImGuiWindowFlags_NoMove;
        if (no_resize)          window_flags |= ImGuiWindowFlags_NoResize;
        if (no_collapse)        window_flags |= ImGuiWindowFlags_NoCollapse;

        ImGui::Begin("Roles Efficiency", nullptr, window_flags);

        static bool bg = true;
        static ImGuiTableFlags flags = ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg;
        if (bg)   flags |= ImGuiTableFlags_Borders;
        if (ImGui::BeginTable("table2", 3, flags))
        {
            int attributesIndex = 0;
            float headerSize = 320.0f;
            ImGui::TableSetupColumn("Defensive", ImGuiTableColumnFlags_WidthFixed, headerSize);
            ImGui::TableSetupColumn("Midfield", ImGuiTableColumnFlags_WidthFixed, headerSize);
            ImGui::TableSetupColumn("Attacking", ImGuiTableColumnFlags_WidthFixed, headerSize);
            ImGui::TableHeadersRow();
            ImGui::TableNextRow();

                // Fill the first column first
            std::vector<RoleEfficiency> DefensiveRoles = player->GetDefensiveRoles();
            for (const auto& role : DefensiveRoles)
            {
               //ImGui::TableNextRow();
               ImGui::TableSetColumnIndex(0);
            //ImGui::Text("%-20s %d", PlayerAttributes[attributesIndex].Name.c_str(), PlayerAttributes[attributesIndex].Value);
               ImGui::Text("%-35s %.2f", role.RoleName.c_str(), role.Value);
        
            }

            std::vector<RoleEfficiency> Midfield = player->GetMidfieldRoles();
            for (const auto& role : Midfield)
            {
                //ImGui::TableNextRow();
                ImGui::TableSetColumnIndex(1);
                //ImGui::Text("%-20s %d", PlayerAttributes[attributesIndex].Name.c_str(), PlayerAttributes[attributesIndex].Value);
                ImGui::Text("%-35s %.2f", role.RoleName.c_str(), role.Value);
            }

            std::vector<RoleEfficiency> Attacking = player->GetAttackingRoles();
            for (const auto& role : Attacking)
            {
                //ImGui::TableNextRow();
                ImGui::TableSetColumnIndex(2);
                //ImGui::Text("%-20s %d", PlayerAttributes[attributesIndex].Name.c_str(), PlayerAttributes[attributesIndex].Value);
                ImGui::Text("%-35s %.2f", role.RoleName.c_str(), role.Value);
            }

            ImGui::EndTable();
        }


        ImGui::Spacing();
        ImGui::Separator(); 
        RoleEfficiency temp = player->GetBestPlayerRole();
        ImGui::Text("Player Best Role: %-35s  %f", temp.RoleName.c_str(), temp.Value);
        ImGui::Separator();
        ImGui::Spacing();

        ImGui::End();
    }

    void RenderAttributeCategory(const std::vector<AttributeWeight>& attributes, const int& initialColumn, const Role& currentRole)
    {
        std::vector<float> weights;
        for (const auto& att : attributes)
        {
            //ImGui::TableNextRow();
            bool RoleHasDataAboutThisAttribute = false;
            float weight = 0.0;
            ImGui::TableSetColumnIndex(initialColumn);
            ImGui::TableSetBgColor(ImGuiTableBgTarget_CellBg, IM_COL32(0, 0, 0, 0)); // Reset background color
            for (const auto& roleAtt : currentRole.Attributes)
            {
                if (att.Name == roleAtt.Name)
                {
                    RoleHasDataAboutThisAttribute = true;
                    weight = roleAtt.Weight;
                    break;
                }
            }
            // no data so just use the default
            if (!RoleHasDataAboutThisAttribute)
            {
                ImGui::TableSetBgColor(ImGuiTableBgTarget_CellBg, IM_COL32(0, 0, 0, 0), initialColumn);
                ImGui::Text("%s", att.Name.c_str());
                int a = ImGui::TableGetRowIndex();
                weights.emplace_back(att.Weight);
            }
            else
            {
                ImGui::TableSetBgColor(ImGuiTableBgTarget_CellBg, IM_COL32(255, 0, 0, 255), initialColumn);
                ImGui::Text("%s", att.Name.c_str());
                weights.emplace_back(weight);
            }
        }

        for (const auto& w : weights)
        {
            ImGui::TableSetColumnIndex(initialColumn + 1);
           // ImGui::TableSetBgColor(ImGuiTableBgTarget_CellBg, IM_COL32(255, 0, 0, 255));
            ImGui::Text("%.1f", w);
            //ImGui::TableSetBgColor(ImGuiTableBgTarget_CellBg, IM_COL32(0, 0, 0, 0)); // Reset background color

        }
    }

    void RenderAllAttributes(const std::vector<AttributeWeight>& attributes, const int& initialColumn, const Role& currentRole)
    {
        int Column = 0;
        std::vector<float> weights;
        ImGui::TableSetColumnIndex(Column);
        for (const auto& att : attributes)
        {
            bool RoleHasDataAboutThisAttribute = false;
            float weight = 0.0;
            ImGui::TableSetBgColor(ImGuiTableBgTarget_CellBg, IM_COL32(0, 0, 0, 0)); // Reset background color
            for (const auto& roleAtt : currentRole.Attributes)
            {
                if (att.Name == roleAtt.Name)
                {
                    RoleHasDataAboutThisAttribute = true;
                    weight = roleAtt.Weight;
                    break;
                }
            }
            int index = ImGui::TableGetColumnIndex();


            // no data so just use the default
            if (!RoleHasDataAboutThisAttribute)
            {
                ImGui::TableSetBgColor(ImGuiTableBgTarget_CellBg, IM_COL32(0, 0, 0, 0));
                //ImGui::Text("%s", att.Name.c_str());
                if (ImGui::BeginMenu((att.Name.c_str())))
                {
                    ImGui::Text("Remove Item");
                    ImGui::EndMenu();
                }
                ImGui::TableNextColumn();
                ImGui::Text("%.1f", att.Weight);
                weights.emplace_back(att.Weight);
            }
            else
            {
                ImGui::TableSetBgColor(ImGuiTableBgTarget_CellBg, IM_COL32(0, 255, 0, 255));
                //ImGui::Text("%s", att.Name.c_str());
                ImGui::Button(att.Name.c_str());
                ImGui::TableNextColumn();
                ImGui::TableSetBgColor(ImGuiTableBgTarget_CellBg, IM_COL32(0, 255, 0, 255));
                ImGui::Text("%.1f", weight);
                weights.emplace_back(weight);
            }
            ImGui::TableNextColumn();
        }

        //for (const auto& w : weights)
        //{
        //    ImGui::TableSetColumnIndex(initialColumn + 1);
        //    // ImGui::TableSetBgColor(ImGuiTableBgTarget_CellBg, IM_COL32(255, 0, 0, 255));
        //    ImGui::Text("%.1f", w);
        //    //ImGui::TableSetBgColor(ImGuiTableBgTarget_CellBg, IM_COL32(0, 0, 0, 0)); // Reset background color

        //}
    }

    void RenderRoleAttributes(const Role& currentRole, const bool& displayAttributes)
    {
        bool RoleSelected = false;

        // setup flags for file uploading window
        static bool no_move = false;
        static bool no_resize = false;
        static bool no_collapse = true;

        ImGuiWindowFlags window_flags = 0;

        if (no_move)            window_flags |= ImGuiWindowFlags_NoMove;
        if (no_resize)          window_flags |= ImGuiWindowFlags_NoResize;
        if (no_collapse)        window_flags |= ImGuiWindowFlags_NoCollapse;
        ImGui::Begin("Role Editor", nullptr, window_flags);

        ImGui::Text("Role Selected: ");
        
        if (displayAttributes)
        {
            ImGui::SameLine();
            ImGui::Text(currentRole.Name.c_str());
            ImGui::Separator();
            if (ImGui::BeginTable("table2", 6))
            {
                int attributesIndex = 0;
                float headerSize = 160.0f;
                float smallHeaderSize = 80.0f;
                ImGui::TableSetupColumn("Technical", ImGuiTableColumnFlags_WidthFixed, headerSize);
                ImGui::TableSetupColumn("Weight", ImGuiTableColumnFlags_WidthFixed, smallHeaderSize);
                ImGui::TableSetupColumn("Mental", ImGuiTableColumnFlags_WidthFixed, headerSize);
                ImGui::TableSetupColumn("Weight", ImGuiTableColumnFlags_WidthFixed, smallHeaderSize);
                ImGui::TableSetupColumn("Physical", ImGuiTableColumnFlags_WidthFixed, headerSize);
                ImGui::TableSetupColumn("Weight", ImGuiTableColumnFlags_WidthFixed, smallHeaderSize);
                ImGui::TableHeadersRow();
                ImGui::TableNextRow();

                //RenderAttributeCategory(TechnicalAttributes, 0, currentRole);
                //RenderAttributeCategory(MentalAttributes, 2, currentRole);
                //RenderAttributeCategory(PhysicalAttributes, 4, currentRole);
                RenderAllAttributes(AllAttributesSorted, 0, currentRole);

                ImGui::EndTable();
            }
        }
        ImGui::End();
    }

    Role RolePressed;
    void RenderEditRolesScreen(std::vector<Role>& allRoles)
    {
        bool RoleSelected = false;

        // setup flags for file uploading window
        static bool no_move = false;
        static bool no_resize = false;
        static bool no_collapse = true;

        ImGuiWindowFlags window_flags = 0;

        if (no_move)            window_flags |= ImGuiWindowFlags_NoMove;
        if (no_resize)          window_flags |= ImGuiWindowFlags_NoResize;
        if (no_collapse)        window_flags |= ImGuiWindowFlags_NoCollapse;
        ImGui::Begin("Role Selector", nullptr, window_flags);

        ImGuiStyle& style = ImGui::GetStyle();
        style.Colors[ImGuiCol_Button] = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);

        if (ImGui::TreeNode("Defensive"))
        {
            ImGui::Indent();
            for (auto& role : allRoles)
            {
                if (role.TypeEnum == Defensive)
                {
                    if (ImGui::Button(role.Name.c_str()))
                    {
                        AttributesDisplayed = true;
                        RolePressed = role;
                    }
                }
            }
            ImGui::Unindent();
            ImGui::TreePop();
        }
        if (ImGui::TreeNode("Midfield"))
        {
            ImGui::Indent();

            for (auto& role : allRoles)
            {
                if (role.TypeEnum == Midfield)
                {
                    if (ImGui::Button(role.Name.c_str()))
                    {
                        AttributesDisplayed = true;
                        RolePressed = role;
                    }
                }
            }
            ImGui::Unindent();
            ImGui::TreePop();
        }
        if (ImGui::TreeNode("Attacking"))
        {
            ImGui::Indent();

            for (auto& role : allRoles)
            {
                if (role.TypeEnum == Attacking)
                {
                    if (ImGui::Button(role.Name.c_str()))
                    {
                        AttributesDisplayed = true;
                        RolePressed = role;
                    }
                }
            }
            ImGui::Unindent();
            ImGui::TreePop();
        }

        style = ImGui::GetStyle();
        style.Colors[ImGuiCol_Button] = ImVec4(0.2f, 0.4f, 0.6f, 1.0f);

        ImGui::End();

        RenderRoleAttributes(RolePressed, AttributesDisplayed);

    }

    
}
