#define GLEW_STATIC

#include "Application.h"

int main(int, char**)
{
    PlayerAnalyzer::Main();
}

//// Main code
//int main(int, char**)
//{
//    glfwSetErrorCallback(glfw_error_callback);
//    if (!glfwInit())
//        return 1;
//
//    const char* glsl_version = "#version 130";
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
//
//    // Create window with graphics context
//    GLFWwindow* window = glfwCreateWindow(1780, 880, "Player Analyzer", nullptr, nullptr);
//    if (window == nullptr)
//        return 1;
//    glfwMakeContextCurrent(window);
//    glfwSwapInterval(1);
//
//    // Setup Dear ImGui context
//    IMGUI_CHECKVERSION();
//    ImGui::CreateContext();
//    ImGuiIO& io = ImGui::GetIO(); (void)io;
//    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
//    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
//    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // Enable Docking
//    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;       // Enable Multi-Viewport / Platform Windows
//    //io.ConfigViewportsNoAutoMerge = true;
//    io.ConfigViewportsNoTaskBarIcon = true;
//   
//    // Setup Dear ImGui style
//    ImGui::StyleColorsDark();
//    //ImGui::StyleColorsLight();
//
//    // When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
//    ImGuiStyle& style = ImGui::GetStyle();
//    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
//    {
//        style.WindowRounding = 0.0f;
//        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
//    }
//
//    // Setup Platform/Renderer backends
//    ImGui_ImplGlfw_InitForOpenGL(window, true);
//    ImGui_ImplOpenGL3_Init(glsl_version);
//
//    io.Fonts->AddFontFromFileTTF("fonts/Roboto-Bold.ttf", 22.0f);
//    io.FontDefault = io.Fonts->AddFontFromFileTTF("fonts/Roboto-Medium.ttf", 22.0f);
//
//    // Our state
//    bool show_demo_window = true;
//    bool show_another_window = false;
//    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
//
//    // my project setup
//
//    std::vector<std::shared_ptr<Player>> AllPlayersLoaded;
//    std::shared_ptr<Player> ActivePlayer;
//
//    glfwSetDropCallback(window, Callback::DragAndDropCallback);
// 
//    TextureManager TextureMgr;
//
//    // create UI Panels
//    FileUploader FileUploaderScreen(false, false, true, std::string("File Uploader"), true);
//    FileUploaderScreen.SetPlayerUploadedRef(ActivePlayer);
//    FileUploaderScreen.SetFileState(Callback::fileUploadState);
//    PlayerAttributesPanel PlayerAttributesScreen(false, false, true, std::string("Player Attributes"), true);
//    RoleEfficiencyPanel RoleEfficiencyScreen(false, false, true, std::string("Player Role Efficiency"), true);
//
//    RoleSelector RoleSelectorScreen(false, false, true, std::string("Role Selector"), true);
//
//    SaveRolePanel SaveRoleScreen(false, false, true, std::string("Save Role"), true, TextureMgr.GetFileImage());
//
//    RoleEditor RoleEditorScreen(false, false, true, std::string("Role Editor"), true, &SaveRoleScreen);
//
//    PlayersLoaded PlayersLoadedScreen(false, false, true, std::string("Players Loaded"), true, TextureMgr.GetPlayerImage());
//
//    RoleSelectorScreen.SetRoleEditor(&RoleEditorScreen);
//    RoleSelectorScreen.AllRoles = BuildRoleDatabase();
//
//    CleanUpDatabase(RoleSelectorScreen.AllRoles);
//    RoleSelectorScreen.SetRolesSelectedMap();
//    std::vector<Role> OriginalDB = RoleSelectorScreen.AllRoles;
//    //PrintArrayOfRoles(AllRoles);
//    RoleSelectorScreen.SetOriginalDBRef(OriginalDB);
//    PlayersLoadedScreen.SetPlayersUploaded(&AllPlayersLoaded);
//
//    CustomRoleLoader CustomRoleLoaderScreen(false, false, true, std::string("Load Files"), true, TextureMgr.GetFileImage(), RoleSelectorScreen.AllRoles);
//
//    Settings SettingsPanel(false, false, true, std::string("Settings"), true);
//    SettingsPanel.SetHighlightRefs(PlayerAttributesScreen.GetPlayersHighlight(), RoleEfficiencyScreen.GetEfficiencyHighlight(), RoleEditorScreen.GetWeightHighlight());
//    
//    // Main loop
//#ifdef __EMSCRIPTEN__
//    // For an Emscripten build we are disabling file-system access, so let's not attempt to do a fopen() of the imgui.ini file.
//    // You may manually call LoadIniSettingsFromMemory() to load settings from your own storage.
//    io.IniFilename = nullptr;
//    EMSCRIPTEN_MAINLOOP_BEGIN
//#else
//    while (!glfwWindowShouldClose(window))
//#endif
//    {
//        // Poll and handle events (inputs, window resize, etc.)
//        // You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
//        // - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application, or clear/overwrite your copy of the mouse data.
//        // - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application, or clear/overwrite your copy of the keyboard data.
//        // Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
//        glfwPollEvents();
//
//        // Start the Dear ImGui frame
//        ImGui_ImplOpenGL3_NewFrame();
//        ImGui_ImplGlfw_NewFrame();
//        ImGui::NewFrame();
//      
//        // our application
//
//        ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());
//
//        if (ImGui::BeginMainMenuBar())
//        {
//            ImGuiIO& io = ImGui::GetIO();
//            auto titleFont = io.Fonts->Fonts[0];
//
//            ImGuiStyle& style = ImGui::GetStyle();
//            style.Colors[ImGuiCol_Button] = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
//            ImGui::PushFont(titleFont);
//
//            if (ImGui::Button("Main Screen"))
//            {
//                //ShowExampleMenuFile();
//                PlayerAnalyzer::SwitchState(PlayerAnalyzer::MAIN_MENU, RoleSelectorScreen.AllRoles, ActivePlayer);
//                //ImGui::EndMenu();
//            }
//            if (ImGui::Button("Edit Players Roles"))
//            {
//                PlayerAnalyzer::SwitchState(PlayerAnalyzer::ROLE_EDITOR, RoleSelectorScreen.AllRoles, NULL, NULL, &SaveRoleScreen);
//
//            }
//            if (ImGui::Button("Load Custom Player Roles"))
//            {
//                PlayerAnalyzer::SwitchState(PlayerAnalyzer::LOAD_FILES, RoleSelectorScreen.AllRoles, NULL, &CustomRoleLoaderScreen);
//
//            }
//            ImGui::PopFont();
//
//            style = ImGui::GetStyle();
//            style.Colors[ImGuiCol_Button] = ImVec4(0.2f, 0.4f, 0.6f, 1.0f);
//            ImGui::EndMainMenuBar();
//        }
//        std::string temp;
//        switch (PlayerAnalyzer::State)
//        {
//            case PlayerAnalyzer::MAIN_MENU:
//
//                FileUploaderScreen.RenderPanel();
//
//                ///////////////// !!!!!!! improve this !!!!!!!!!!
//
//                if (FileUploaderScreen.GetNewPlayerUploaded())
//                {
//                    ActivePlayer = FileUploaderScreen.GetPlayerUploaded();
//                }
//
//                if (ActivePlayer != nullptr)
//                {
//
//                    int index = IsPlayerAlreadyLoaded(ActivePlayer->GetUniqueID(), AllPlayersLoaded);
//                    if (index != -1)
//                    {
//                        ActivePlayer = AllPlayersLoaded[index];
//                        ActivePlayer->UpdateEfficiency(RoleSelectorScreen.AllRoles);
//                    }
//                    else
//                    {
//                        AllPlayersLoaded.emplace_back(ActivePlayer);
//                        ActivePlayer->CalculateEfficiencyAllRoles(RoleSelectorScreen.AllRoles);
//                    }
//                }
//                PlayersLoadedScreen.SetCurrentPlayer(ActivePlayer);
//                PlayersLoadedScreen.RenderPanel();
//                ActivePlayer = PlayersLoadedScreen.GetCurrentPlayer();
//
//                PlayerAttributesScreen.SetPlayerToDisplay(ActivePlayer);
//                PlayerAttributesScreen.RenderPanel();
//
//                RoleEfficiencyScreen.SetPlayerToDisplay(ActivePlayer);
//                RoleEfficiencyScreen.RenderPanel();
//                ////////////////////////////////////////////////////
//           
//                break;
//        case PlayerAnalyzer::ROLE_EDITOR:
//            RoleSelectorScreen.RenderPanel();
//            SaveRoleScreen.RenderPanel();
//            break;
//        case PlayerAnalyzer::LOAD_FILES:
//            CustomRoleLoaderScreen.RenderPanel();
//            if (CustomRoleLoaderScreen.WasFileLoadedByUser())
//            {
//                // resetting the database
//                RoleSelectorScreen.AllRoles = OriginalDB;
//                UpdateRoleFromCustomFile(RoleSelectorScreen.AllRoles, CustomRoleLoaderScreen.GetFileToLoad());
//            }
//            SettingsPanel.RenderPanel();
//            ImGui::ShowDemoWindow();
//            break;
//        default:
//            break;
//        }
//
//
//        // Rendering
//        ImGui::Render();
//        int display_w, display_h;
//        // ---- we don't need to render opengl stuff
//        //glfwGetFramebufferSize(window, &display_w, &display_h);
//        //glViewport(0, 0, display_w, display_h);
//        //glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
//        //glClear(GL_COLOR_BUFFER_BIT);
//        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
//
//        // Update and Render additional Platform Windows
//        // (Platform functions may change the current OpenGL context, so we save/restore it to make it easier to paste this code elsewhere.
//        //  For this specific demo app we could also call glfwMakeContextCurrent(window) directly)
//        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
//        {
//            GLFWwindow* backup_current_context = glfwGetCurrentContext();
//            ImGui::UpdatePlatformWindows();
//            ImGui::RenderPlatformWindowsDefault();
//            glfwMakeContextCurrent(backup_current_context);
//        }
//
//        glfwSwapBuffers(window);
//    }
//#ifdef __EMSCRIPTEN__
//    EMSCRIPTEN_MAINLOOP_END;
//#endif
//
//    // Cleanup
//    ImGui_ImplOpenGL3_Shutdown();
//    ImGui_ImplGlfw_Shutdown();
//    ImGui::DestroyContext();
//
//    glfwDestroyWindow(window);
//    glfwTerminate();
//
//    return 0;
//}
