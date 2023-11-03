#include "Application.h"
#include "Database.h"
#include "glfw_callbacks.hpp"
#include "TextureManager.h"
#include "Player.h"
#include "PlayerAttributesPanel.h"
#include "FileUploader.h"
#include "RoleEfficiencyPanel.h"
#include "RoleEditor.h"
#include "RoleSelector.h"
#include "SaveRolePanel.h"
#include "PlayersLoaded.h"
#include "CustomRoleLoader.h"
#include "Settings.h"
#include "PlayerAttributeComparison.h"
#include "SelectPlayers.h"
namespace PlayerAnalyzer
{
    bool InitGlfw()
    {
        glfwSetErrorCallback(glfw_error_callback);
        if (!glfwInit())
            return false;

        glsl_version = "#version 130";
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

        // Create window with graphics context
        Window = glfwCreateWindow(1780, 880, "Player Analyzer", nullptr, nullptr);
        if (Window == nullptr)
            return false;
        glfwMakeContextCurrent(Window);
        glfwSwapInterval(1);

        // set drop call back
        // used for detecting filedrop
        glfwSetDropCallback(Window, Callback::DragAndDropCallback);

        return true;
    }

    void InitImGui()
    {
        // Setup Dear ImGui context
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // Enable Docking
        io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;       // Enable Multi-Viewport / Platform Windows
        //io.ConfigViewportsNoAutoMerge = true;
        io.ConfigViewportsNoTaskBarIcon = true;

        // Setup Dear ImGui style
        ImGui::StyleColorsDark();
        //ImGui::StyleColorsLight();

        // When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
        ImGuiStyle& style = ImGui::GetStyle();
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            style.WindowRounding = 0.0f;
            style.Colors[ImGuiCol_WindowBg].w = 1.0f;
        }

        // Setup Platform/Renderer backends
        ImGui_ImplGlfw_InitForOpenGL(Window, true);
        ImGui_ImplOpenGL3_Init(glsl_version);

        io.Fonts->AddFontFromFileTTF("fonts/Roboto-Bold.ttf", 22.0f);
        io.FontDefault = io.Fonts->AddFontFromFileTTF("fonts/Roboto-Medium.ttf", 22.0f);
    }

    void NewFrame()
    {
        glfwPollEvents();
        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());
    }

    void Cleanup()
    {
        // Cleanup
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();

        glfwDestroyWindow(Window);
        glfwTerminate();
    }

    void ImGuiRenderer()
    {
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
         //ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
         // Update and Render additional Platform Windows
         // (Platform functions may change the current OpenGL context, so we save/restore it to make it easier to paste this code elsewhere.
         //  For this specific demo app we could also call glfwMakeContextCurrent(window) directly)
        if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            GLFWwindow* backup_current_context = glfwGetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            glfwMakeContextCurrent(backup_current_context);
        }
        glfwSwapBuffers(Window);
    }


    void Main()
    {
        if (!InitGlfw())
            return;
        InitImGui();

        //Init Role Database
        std::vector<Role> OriginalDB;
        std::vector<Role> AllRoles;
        InitDatabase(AllRoles, OriginalDB);

        // Keep Track of players
        std::vector<Player> AllPlayersLoaded;
        Player* ActivePlayer = NULL;

        TextureManager TextureMgr;

        //Main Menu UI Panels
        FileUploader FileUploaderScreen(false, false, true, std::string("File Uploader"), true);
        PlayerAttributesPanel PlayerAttributesScreen(false, false, true, std::string("Player Attributes"), true);
        RoleEfficiencyPanel RoleEfficiencyScreen(false, false, true, std::string("Player Role Efficiency"), true);
        PlayersLoaded PlayersLoadedScreen(false, false, true, std::string("Players Loaded"), true, TextureMgr.GetPlayerImage());

        // Edit Roles Menu UI Panels
        RoleSelector RoleSelectorScreen(false, false, true, std::string("Role Selector"), true);
        SaveRolePanel SaveRoleScreen(false, false, true, std::string("Save Role"), true, TextureMgr.GetFileImage());
        RoleEditor RoleEditorScreen(false, false, true, std::string("Role Editor"), true, &SaveRoleScreen);

        // LoadFiles/Settings Menu UI Panels
        Settings SettingsPanel(false, false, true, std::string("Settings"), true);
        CustomRoleLoader CustomRoleLoaderScreen(false, false, true, std::string("Load Files"), true, TextureMgr.GetFileImage(), AllRoles);

        //Player Comparison UI Panels
        RoleSelector RoleSelectorPlComp(false, false, true, std::string("Role Selector Comparison"), true);
        PlayerAttributeComparison AttributeComparison(false, false, true, std::string("Player Comparison"), true);
        SelectPlayers PlayersSelection(false, false, true, std::string("Select Players"), true, TextureMgr.GetPlayerImage());

        // Init all UI Panels of the main menu
        InitMainMenu(FileUploaderScreen, RoleEfficiencyScreen, PlayersLoadedScreen, PlayerAttributesScreen, AllRoles, AllPlayersLoaded);

        // Init ALl UI Panels in Role Editor Screen
        InitEditRolesMenu(RoleSelectorScreen, RoleEditorScreen, AllRoles, OriginalDB);

        // Init All UI Panels in Load Files / Settings Menu
        InitLoadFilesMenu(SettingsPanel, RoleEfficiencyScreen, PlayerAttributesScreen, RoleEditorScreen);

        // Init all UI Panels of player comparison Menu
        InitPlayerComparisonMenu(RoleSelectorPlComp, AttributeComparison, PlayersSelection, AllRoles, PlayerAttributesScreen.GetPlayersHighlight(), AllPlayersLoaded);

       
        while (!glfwWindowShouldClose(Window))
        {
            NewFrame();

            RenderMainMenuBar(RoleSelectorScreen, SaveRoleScreen, ActivePlayer, CustomRoleLoaderScreen, State, AllPlayersLoaded);

            switch (State)
            {
                case AppState::MAIN_MENU:

                    RenderMainMenu(FileUploaderScreen, RoleEfficiencyScreen, PlayersLoadedScreen, PlayerAttributesScreen, ActivePlayer, AllPlayersLoaded, AllRoles);
                    break;

                case AppState::ROLE_EDITOR:

                    RenderEditRolesMenu(RoleSelectorScreen, SaveRoleScreen);
                    break;

                case AppState::LOAD_FILES:

                    RenderLoadFilesMenu(SettingsPanel, CustomRoleLoaderScreen, AllRoles, OriginalDB);
                    break;

                case AppState::PLAYER_COMPARISON:

                    RenderPlayerComparisonMenu(RoleSelectorPlComp, PlayersSelection, AttributeComparison);
                    break;
                default:
                    break;
            }

            ImGuiRenderer();
        }

        Cleanup();
    }

   
    void SwitchState(const AppState& newState, const std::vector<Role>& allRoles, Player* player, CustomRoleLoader* roleLoader, SaveRolePanel* roleSaver)
    {
        switch (newState)
        {
        case AppState::MAIN_MENU:
            if (player != NULL)
            {
                player->UpdateEfficiency(allRoles);
            }
            break;
        case AppState::ROLE_EDITOR:
            if (roleSaver != NULL)
            {
                roleSaver->ClearFiles();
                roleSaver->LoadFilesInDirectory("custom_roles");
            }
            break;
        case AppState::LOAD_FILES:
            if (roleLoader != NULL)
            {
                roleLoader->ClearFiles();
                roleLoader->LoadFilesInDirectory("custom_roles");
            }
            break;
        case AppState::PLAYER_COMPARISON:
           
            
        default:
            break;
        }
    }

    void RenderMainMenuBar(RoleSelector& selector, SaveRolePanel& saveRole, Player* player, CustomRoleLoader& roleLoader, AppState& state, std::vector<Player>& allPlayers)
    {
        if (ImGui::BeginMainMenuBar())
        {
            ImGuiIO& io = ImGui::GetIO();
            auto titleFont = io.Fonts->Fonts[0];

            ImGuiStyle& style = ImGui::GetStyle();
            ImVec4 previousColor = style.Colors[ImGuiCol_Header];
            style.Colors[ImGuiCol_Header] = style.Colors[ImGuiCol_HeaderActive];
            //style.Colors[ImGuiCol_S] = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
            ImGui::PushFont(titleFont);

            bool selection[4] = { false, false, false, false };
            selection[(int)state] = true;
            ImGuiSelectableFlags_ flag = ImGuiSelectableFlags_AllowDoubleClick;
            ImVec2 size = ImGui::CalcTextSize(" Main Screen ");
            size.y = size.y * 1.5;
            if (ImGui::Selectable(" Main Screen ", selection[0], flag, size))
            {
                //ShowExampleMenuFile();
                state = AppState::MAIN_MENU;
                SwitchState(AppState::MAIN_MENU, *selector.AllRoles, player);
               
            }
            flag = ImGuiSelectableFlags_AllowDoubleClick;
            size = ImGui::CalcTextSize(" Edit Players Roles ");
            size.y = size.y * 1.5;

            if (ImGui::Selectable(" Edit Players Roles ", selection[1], flag, size))
            {
                state = AppState::ROLE_EDITOR;

                SwitchState(AppState::ROLE_EDITOR, *selector.AllRoles, NULL, NULL, &saveRole);

            }
            flag = ImGuiSelectableFlags_AllowDoubleClick;
            size = ImGui::CalcTextSize(" Load Custom Player Roles ");
            size.y = size.y * 1.5;

            if (ImGui::Selectable(" Load Custom Player Roles ", selection[2], flag, size))
            {
                state = AppState::LOAD_FILES;

                SwitchState(AppState::LOAD_FILES, *selector.AllRoles, NULL, &roleLoader, NULL);

            }
            flag = ImGuiSelectableFlags_AllowDoubleClick;
            size = ImGui::CalcTextSize(" Player Comparison ");
            size.y = size.y * 1.5;

            if (ImGui::Selectable(" Player Comparison ", selection[3], flag, size))
            {
                //RoleSelector::EditorChangedRole = true;
                state = AppState::PLAYER_COMPARISON;

                for (auto& pl : allPlayers)
                {
                    pl.UpdateEfficiency(*selector.AllRoles);
                }

                SwitchState(state, *selector.AllRoles, NULL, &roleLoader, NULL);
            }
            ImGui::PopFont();

            style = ImGui::GetStyle();
            style.Colors[ImGuiCol_Header] = previousColor;
            ImGui::EndMainMenuBar();
        }
    }

    void InitDatabase(std::vector<Role>& out_AllRoles, std::vector<Role>& out_OriginalDB)
    {
        out_OriginalDB = BuildRoleDatabase();
        CleanUpDatabase(out_OriginalDB);
        out_AllRoles = BuildRoleDatabase();
        CleanUpDatabase(out_AllRoles);
    }

    void InitMainMenu(FileUploader& uploader, RoleEfficiencyPanel& efficiencyPanel, PlayersLoaded& loadedPlayersScreen,
                        PlayerAttributesPanel& attributes, const std::vector<Role>& allRoles, std::vector<Player>& allPlayers)
    {
        // Init Main Menu
        // set fileUploader references to the active player and the file upload state
        uploader.SetFileState(Callback::fileUploadState);
        efficiencyPanel.InitRoleSelectedMap(allRoles);
        loadedPlayersScreen.SetPlayersUploaded(&allPlayers);
        attributes.SetRoleSelected(efficiencyPanel.GetRoleSelected());
    }

    void InitEditRolesMenu(RoleSelector& selector, RoleEditor& editor, std::vector<Role>& allRoles, std::vector<Role>& originalDB)
    {
        selector.SetRoleEditor(&editor);
        selector.SetAllRoles(allRoles);
        selector.SetOriginalDBRef(originalDB);

    }

    void InitLoadFilesMenu(Settings& settings, RoleEfficiencyPanel& efficiencyPanel, PlayerAttributesPanel& attributes, RoleEditor& editor)
    {
        settings.SetHighlightRefs(attributes.GetPlayersHighlight(), efficiencyPanel.GetEfficiencyHighlight(), editor.GetWeightHighlight());
    }

    void InitPlayerComparisonMenu(RoleSelector& selector, PlayerAttributeComparison& comparison, SelectPlayers& playersSelection, std::vector<Role>& allRoles,
                                    std::shared_ptr<Highlight<int>> highlight, std::vector<Player>& allPlayers)
    {
        selector.SetAllRoles(allRoles);

        comparison.SetPlayersHighlight(highlight);
        comparison.SetRoleSelected(selector.GetRoleSelected());

        playersSelection.SetPlayersUploaded(&allPlayers);
        playersSelection.SetAttributeComparisonRef(&comparison);
    }

    void RenderMainMenu(FileUploader& uploader, RoleEfficiencyPanel& efficiencyPanel, PlayersLoaded& loadedPlayersScreen, PlayerAttributesPanel& attributes,
                            Player*& activePlayer, std::vector<Player>& allPlayers, const std::vector<Role>& allRoles)
    {
        // render file uploading
        uploader.RenderPanel();
        // whenever there is a new player uploaded
        if (uploader.GetNewPlayerUploaded())
        {
            // retrive it from the uploader class
            std::vector<Player> players = uploader.GetAllPlayersUploaded();
            for (auto& pl : players)
            {
                int index = IsPlayerAlreadyLoaded(pl.GetUniqueID(), allPlayers);
                if (index != -1)
                {
                    // it is not new, so just get the player that is already in the vector
                    //ActivePlayer = AllPlayersLoaded[index];
                    pl.UpdateEfficiency(allRoles);
                }
                else
                {
                    pl.CalculateEfficiencyAllRoles(allRoles);
                    allPlayers.emplace_back(pl);
                }

            }
            if (allPlayers.size() > 0)
                activePlayer = &allPlayers[allPlayers.size() - 1];

        }
        // render players loaded
        loadedPlayersScreen.SetCurrentPlayer(activePlayer);
        loadedPlayersScreen.RenderPanel();
        activePlayer = loadedPlayersScreen.GetCurrentPlayer();
        // render efficiency screen
        EfficiencyScreen(efficiencyPanel, activePlayer, allRoles);
        // render playerAttributes
        attributes.SetFirstPlayer(activePlayer);
        attributes.RenderPanel();
    }

    void RenderEditRolesMenu(RoleSelector& selector, SaveRolePanel& roleSaver)
    {
        selector.RenderPanel();
        roleSaver.RenderPanel();
    }

    void RenderLoadFilesMenu(Settings& settings, CustomRoleLoader& roleLoader, std::vector<Role>& allRoles, std::vector<Role>& originalDB)
    {
        roleLoader.RenderPanel();
        if (roleLoader.WasFileLoadedByUser())
        {
            // resetting the database
            allRoles = originalDB;
            UpdateRoleFromCustomFile(allRoles, roleLoader.GetFileToLoad());
        }
        settings.RenderPanel();
        ImGui::ShowDemoWindow();
    }

    void RenderPlayerComparisonMenu(RoleSelector& selector, SelectPlayers& playerSelection, PlayerAttributeComparison& comparison)
    {
        selector.RenderPanel();
        playerSelection.RenderPanel();
        comparison.SetRoleSelected(selector.GetRoleSelected());
        comparison.RenderPanel();
    }

    void EfficiencyScreen(RoleEfficiencyPanel& efficiency, Player* player, const std::vector<Role>& roles)
    {
        // render role efficiency
        efficiency.SetPlayerToDisplay(player);
        efficiency.RenderPanel();
        Role* temp = efficiency.GetRoleSelected();
        if (temp->ID != 0)
        {
            temp->Attributes = GetAttributesOfRole(temp->ID, roles);
        }
    }

    int IsPlayerAlreadyLoaded(const uint64_t& ID, std::vector<Player>& allPlayers)
    {
        int i = 0;
        for (auto& it : allPlayers)
        {
            if (ID == it.GetUniqueID())
            {
                return i;
            }
            i++;
        }

        return -1;
    }

    std::vector<AttributeWeight> GetAttributesOfRole(uint64_t ID, const std::vector<Role>& allRoles)
    {
        std::vector<AttributeWeight> attributes;
        for (const auto& role : allRoles)
        {
            if (ID == role.ID)
            {
                for (const auto& att : role.Attributes)
                {
                    attributes.emplace_back(att);
                }
                break;
            }
        }

        return attributes;
    }
    
}
