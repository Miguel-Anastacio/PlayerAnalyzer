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

    void Cleanup()
    {
        // Cleanup
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();

        glfwDestroyWindow(Window);
        glfwTerminate();
    }

    void ResetRenderer()
    {
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

        // Keep Track of players
        std::vector<Player> AllPlayersLoaded;
        //std::shared_ptr<Player> ActivePlayer;
        Player* ActivePlayer = NULL;

        TextureManager TextureMgr;

        FileUploader FileUploaderScreen(false, false, true, std::string("File Uploader"), true);

        PlayerAttributesPanel PlayerAttributesScreen(false, false, true, std::string("Player Attributes"), true);
        RoleEfficiencyPanel RoleEfficiencyScreen(false, false, true, std::string("Player Role Efficiency"), true);

        RoleSelector RoleSelectorScreen(false, false, true, std::string("Role Selector"), true);

        SaveRolePanel SaveRoleScreen(false, false, true, std::string("Save Role"), true, TextureMgr.GetFileImage());

        RoleEditor RoleEditorScreen(false, false, true, std::string("Role Editor"), true, &SaveRoleScreen);

        PlayersLoaded PlayersLoadedScreen(false, false, true, std::string("Players Loaded"), true, TextureMgr.GetPlayerImage());

        Settings SettingsPanel(false, false, true, std::string("Settings"), true);

        // set fileUploader references to the active player and the file upload state
        //FileUploaderScreen.SetPlayerUploadedRef(ActivePlayer);
        FileUploaderScreen.SetFileState(Callback::fileUploadState);

        RoleSelectorScreen.SetRoleEditor(&RoleEditorScreen);
        // make this parte cleaner
        std::vector<Role> OriginalDB = BuildRoleDatabase();
        CleanUpDatabase(OriginalDB);
        std::vector<Role> AllRoles = BuildRoleDatabase();
        CleanUpDatabase(AllRoles);
        RoleSelectorScreen.SetAllRoles(AllRoles);

        RoleSelectorScreen.SetRolesSelectedMap();
        //PrintArrayOfRoles(AllRoles);
        RoleSelectorScreen.SetOriginalDBRef(OriginalDB);

        // set reference to vector that keeps track of players loaded
        PlayersLoadedScreen.SetPlayersUploaded(&AllPlayersLoaded);

        CustomRoleLoader CustomRoleLoaderScreen(false, false, true, std::string("Load Files"), true, TextureMgr.GetFileImage(), *RoleSelectorScreen.AllRoles);

        // references to the highlight structure used by the UI panels that do color coding
        SettingsPanel.SetHighlightRefs(PlayerAttributesScreen.GetPlayersHighlight(), RoleEfficiencyScreen.GetEfficiencyHighlight(), RoleEditorScreen.GetWeightHighlight());

        PlayerAttributesScreen.SetRoleSelected(RoleEfficiencyScreen.GetRoleSelected());

        AppState State = AppState::MAIN_MENU;

        // Player Comparison Window stuff
        RoleSelector RoleSelectorPlComp(false, false, true, std::string("Role Selector Comparison"), true);
        RoleSelectorPlComp.SetAllRoles(*RoleSelectorScreen.AllRoles);
        PlayerAttributeComparison AttributeComparison(false, false, true, std::string("Player Comparison"), true);

        AttributeComparison.SetPlayersHighlight(PlayerAttributesScreen.GetPlayersHighlight());
        AttributeComparison.SetRoleSelected(RoleSelectorPlComp.GetRoleSelected());

        SelectPlayers PlayersSelection(false, false, true, std::string("Select Players"), true, TextureMgr.GetPlayerImage());
        PlayersSelection.SetPlayersUploaded(&AllPlayersLoaded);
        PlayersSelection.SetAttributeComparisonRef(&AttributeComparison);

        while (!glfwWindowShouldClose(Window))
        {
            glfwPollEvents();
            // Start the Dear ImGui frame
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

            ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());

            RenderMainMenuBar(RoleSelectorScreen, SaveRoleScreen, ActivePlayer, CustomRoleLoaderScreen, State, AllPlayersLoaded);

            switch (State)
            {
                case AppState::MAIN_MENU:

                    // render file uploading
                    FileUploaderScreen.RenderPanel();
                    // whenever there is a new player uploaded
                    if (FileUploaderScreen.GetNewPlayerUploaded())
                    {
                        // retrive it from the uploader class
                        std::vector<Player> players = FileUploaderScreen.GetAllPlayersUploaded();
                        for (auto& pl : players)
                        {
                            int index = IsPlayerAlreadyLoaded(pl.GetUniqueID(), AllPlayersLoaded);
                            if (index != -1)
                            {
                                // it is not new, so just get the player that is already in the vector
                                //ActivePlayer = AllPlayersLoaded[index];
                                pl.UpdateEfficiency(*RoleSelectorScreen.AllRoles);
                            }
                            else
                            {
                                pl.CalculateEfficiencyAllRoles(*RoleSelectorScreen.AllRoles);
                                AllPlayersLoaded.emplace_back(pl);
                            }
            
                        }
                        if (AllPlayersLoaded.size() > 0)
                            ActivePlayer = &AllPlayersLoaded[AllPlayersLoaded.size() - 1];



                        //ActivePlayer = FileUploaderScreen.GetPlayerUploaded();
                        //if (ActivePlayer != nullptr)
                        //{
                        //    // make sure it is unique (prevents the same file from being uploaded
                        //    // BUG - if a file is added by draging and then added by file name there will be two players with the same attributes
                        //    int index = IsPlayerAlreadyLoaded(ActivePlayer->GetUniqueID(), AllPlayersLoaded);
                        //    if (index != -1)
                        //    {
                        //        // it is not new, so just get the player that is already in the vector
                        //        ActivePlayer = AllPlayersLoaded[index];
                        //        ActivePlayer->UpdateEfficiency(*RoleSelectorScreen.AllRoles);
                        //    }
                        //    else
                        //    {
                        //        AllPlayersLoaded.emplace_back(ActivePlayer);
                        //        ActivePlayer->CalculateEfficiencyAllRoles(*RoleSelectorScreen.AllRoles);
                        //    }
                        //}
                    }
                    // render players loaded
                    PlayersLoadedScreen.SetCurrentPlayer(ActivePlayer);
                    PlayersLoadedScreen.RenderPanel();
                    ActivePlayer = PlayersLoadedScreen.GetCurrentPlayer();

                    // render role efficiency
                    RoleEfficiencyScreen.SetPlayerToDisplay(ActivePlayer);
                    RoleEfficiencyScreen.RenderPanel();
                    // render playerAttributes
                    PlayerAttributesScreen.SetFirstPlayer(ActivePlayer);
                    PlayerAttributesScreen.RenderPanel();

                    break;

                case AppState::ROLE_EDITOR:

                    RoleSelectorScreen.RenderPanel();
                    SaveRoleScreen.RenderPanel();
                    break;

                case AppState::LOAD_FILES:
                    CustomRoleLoaderScreen.RenderPanel();
                    if (CustomRoleLoaderScreen.WasFileLoadedByUser())
                    {
                        // resetting the database
                        *RoleSelectorScreen.AllRoles = OriginalDB;
                        UpdateRoleFromCustomFile(*RoleSelectorScreen.AllRoles, CustomRoleLoaderScreen.GetFileToLoad());
                    }
                    SettingsPanel.RenderPanel();
                    ImGui::ShowDemoWindow();
                    break;

                case AppState::PLAYER_COMPARISON:
                    RoleSelectorPlComp.RenderPanel();
                    PlayersSelection.RenderPanel();
                    AttributeComparison.SetRoleSelected(RoleSelectorPlComp.GetRoleSelected());
                    AttributeComparison.RenderPanel();
                    break;
                default:
                    break;
            }
            // Rendering
            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());


            ResetRenderer();
        }

        Cleanup();
    }

    //void Run()
    //{
    //    while (!glfwWindowShouldClose(Window))
    //    {
    //        glfwPollEvents();

    //        // Start the Dear ImGui frame
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
          /*  if (selector != NULL && editor != NULL)
            {
                selector->SetRoleEditor(editor);
            }*/
            break;
        case AppState::LOAD_FILES:
            if (roleLoader != NULL)
            {
                roleLoader->ClearFiles();
                roleLoader->LoadFilesInDirectory("custom_roles");
            }
            break;
        case AppState::PLAYER_COMPARISON:
           
            /*if (selector != NULL)
            {
                selector->SetRoleEditor(NULL);
            }*/
        default:
            break;
        }
        //State = newState;
    }
   
   
    //        ImGui_ImplOpenGL3_NewFrame();
    //        ImGui_ImplGlfw_NewFrame();
    //        ImGui::NewFrame();

    //        // our application

    //        ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());
    //    }
    //}

    void RenderMainMenuBar(RoleSelector& selector, SaveRolePanel& saveRole, Player* player, CustomRoleLoader& roleLoader, AppState& state, std::vector<Player>& allPlayers)
    {
        if (ImGui::BeginMainMenuBar())
        {
            ImGuiIO& io = ImGui::GetIO();
            auto titleFont = io.Fonts->Fonts[0];

            ImGuiStyle& style = ImGui::GetStyle();
            style.Colors[ImGuiCol_Button] = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
            ImGui::PushFont(titleFont);

            if (ImGui::Button("Main Screen"))
            {
                //ShowExampleMenuFile();
                state = AppState::MAIN_MENU;
                SwitchState(AppState::MAIN_MENU, *selector.AllRoles, player);
                //ImGui::EndMenu();
            }
            if (ImGui::Button("Edit Players Roles"))
            {
                state = AppState::ROLE_EDITOR;

                SwitchState(AppState::ROLE_EDITOR, *selector.AllRoles, NULL, NULL, &saveRole);

            }
            if (ImGui::Button("Load Custom Player Roles"))
            {
                state = AppState::LOAD_FILES;

                SwitchState(AppState::LOAD_FILES, *selector.AllRoles, NULL, &roleLoader, NULL);

            }
            if (ImGui::Button("Player Comparison"))
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
            style.Colors[ImGuiCol_Button] = ImVec4(0.2f, 0.4f, 0.6f, 1.0f);
            ImGui::EndMainMenuBar();
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

    
}
