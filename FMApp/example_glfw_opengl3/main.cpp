#define GLEW_STATIC
#include "glew.h"
#include "boilerplate.h"

#include "glfw_callbacks.hpp"

#include "PlayerAttributesPanel.h"
#include "FileUploader.h"
#include "RoleEfficiencyPanel.h"
#include "RoleEditor.h"
#include "RoleSelector.h"
#include "SaveRolePanel.h"

#include "Player.h"
#include "Database.h"
#include "PlayerAnalyzerApp.hpp"
//#include "UI.hpp"


int IsPlayerAlreadyLoaded(std::string name, const std::vector<std::shared_ptr<Player>>& allPlayers)
{
    int i = 0;
    for (auto& it : allPlayers)
    {

        if (name == it->GetName())
        {
            return i;
        }
        i++;
    }

    return -1;
}

// Main code
int main(int, char**)
{
    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit())
        return 1;

    // Decide GL+GLSL versions
#if defined(IMGUI_IMPL_OPENGL_ES2)
    // GL ES 2.0 + GLSL 100
    const char* glsl_version = "#version 100";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
#elif defined(__APPLE__)
    // GL 3.2 + GLSL 150
    const char* glsl_version = "#version 150";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // Required on Mac
#else
    // GL 3.0 + GLSL 130
    const char* glsl_version = "#version 130";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // 3.0+ only
#endif

    // Create window with graphics context
    GLFWwindow* window = glfwCreateWindow(1280, 720, "Player Analyzer", nullptr, nullptr);
    if (window == nullptr)
        return 1;
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // Enable Docking
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;       // Enable Multi-Viewport / Platform Windows
    //io.ConfigViewportsNoAutoMerge = true;
    //io.ConfigViewportsNoTaskBarIcon = true;
   
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
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    // Load Fonts
    // - If no fonts are loaded, dear imgui will use the default font. You can also load multiple fonts and use ImGui::PushFont()/PopFont() to select them.
    // - AddFontFromFileTTF() will return the ImFont* so you can store it if you need to select the font among multiple.
    // - If the file cannot be loaded, the function will return a nullptr. Please handle those errors in your application (e.g. use an assertion, or display an error and quit).
    // - The fonts will be rasterized at a given size (w/ oversampling) and stored into a texture when calling ImFontAtlas::Build()/GetTexDataAsXXXX(), which ImGui_ImplXXXX_NewFrame below will call.
    // - Use '#define IMGUI_ENABLE_FREETYPE' in your imconfig file to use Freetype for higher quality font rendering.
    // - Read 'docs/FONTS.md' for more instructions and details.
    // - Remember that in C/C++ if you want to include a backslash \ in a string literal you need to write a double backslash \\ !
    // - Our Emscripten build process allows embedding fonts to be accessible at runtime from the "fonts/" folder. See Makefile.emscripten for details.
    //io.Fonts->AddFontDefault();
    io.Fonts->AddFontFromFileTTF("fonts/Roboto-Bold.ttf", 24.0f);
 
    io.FontDefault = io.Fonts->AddFontFromFileTTF("fonts/Roboto-Medium.ttf", 22.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/DroidSans.ttf", 16.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/Roboto-Medium.ttf", 16.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/Cousine-Regular.ttf", 15.0f);
    //ImFont* font = io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\ArialUni.ttf", 18.0f, nullptr, io.Fonts->GetGlyphRangesJapanese());
    //IM_ASSERT(font != nullptr);

    // Our state
    bool show_demo_window = true;
    bool show_another_window = false;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);


    // my project setup
    std::vector<std::shared_ptr<Player>> AllPlayersLoaded;
    std::shared_ptr<Player> ActivePlayer;




    glfwSetDropCallback(window, Callback::DragAndDropCallback);
    bool state = true;

    TextureManager TextureMgr;

    // create UI Panels
    FileUploader FileUploaderScreen(false, false, true, std::string("File Uploader"), true);
    PlayerAttributesPanel PlayerAttributesScreen(false, false, true, std::string("Player Attributes"), true);
    RoleEfficiencyPanel RoleEfficiencyScreen(false, false, true, std::string("Player Role Efficiency"), true);

    RoleSelector RoleSelectorScreen(false, false, true, std::string("Role Selector"), true);


    CustomRoleLoader CustomRoleLoaderScreen(false, false, true, std::string("Load Files"), true, TextureMgr.GetImage());

    SaveRolePanel SaveRoleScreen(false, false, true, std::string("Save Role"), true, TextureMgr.GetImage());

    RoleEditor RoleEditorScreen(false, false, true, std::string("Role Editor"), true, &SaveRoleScreen);

    RoleSelectorScreen.SetRoleEditor(&RoleEditorScreen);
    RoleSelectorScreen.AllRoles = BuildRoleDatabase();

    CleanUpDatabase(RoleSelectorScreen.AllRoles);
    std::vector<Role> OriginalDB = RoleSelectorScreen.AllRoles;
    //PrintArrayOfRoles(AllRoles);

    
    // Main loop
#ifdef __EMSCRIPTEN__
    // For an Emscripten build we are disabling file-system access, so let's not attempt to do a fopen() of the imgui.ini file.
    // You may manually call LoadIniSettingsFromMemory() to load settings from your own storage.
    io.IniFilename = nullptr;
    EMSCRIPTEN_MAINLOOP_BEGIN
#else
    while (!glfwWindowShouldClose(window))
#endif
    {
        // Poll and handle events (inputs, window resize, etc.)
        // You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
        // - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application, or clear/overwrite your copy of the mouse data.
        // - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application, or clear/overwrite your copy of the keyboard data.
        // Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
        glfwPollEvents();

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
      
        // our application

        ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());

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
                App::SwitchState(App::MAIN_MENU, RoleSelectorScreen.AllRoles, ActivePlayer);
                //ImGui::EndMenu();
            }
            if (ImGui::Button("Edit Players Roles"))
            {
                App::SwitchState(App::ROLE_EDITOR, RoleSelectorScreen.AllRoles, NULL, NULL, &SaveRoleScreen);

            }
            if (ImGui::Button("Load Custom Player Roles"))
            {
                App::SwitchState(App::LOAD_FILES, RoleSelectorScreen.AllRoles, NULL, &CustomRoleLoaderScreen);

            }
            ImGui::PopFont();

            style = ImGui::GetStyle();
            style.Colors[ImGuiCol_Button] = ImVec4(0.2f, 0.4f, 0.6f, 1.0f);
            ImGui::EndMainMenuBar();
        }
        std::string temp;
        switch (App::State)
        {
            case App::MAIN_MENU:
                FileUploaderScreen.SetFileState(Callback::fileUploadState);
                FileUploaderScreen.RenderPanel();
                Callback::fileUploadState = FileUploaderScreen.GetFileState();
                ActivePlayer = FileUploaderScreen.GetPlayerUploaded();
                if (ActivePlayer != nullptr)
                {
                    int index = IsPlayerAlreadyLoaded(ActivePlayer->GetName(), AllPlayersLoaded);
                    if (index != -1)
                    {
                        ActivePlayer = AllPlayersLoaded[index];
                        ActivePlayer->UpdateEfficiency(RoleSelectorScreen.AllRoles);
                    }
                    else
                    {
                        AllPlayersLoaded.emplace_back(ActivePlayer);
                        ActivePlayer->CalculateEfficiencyAllRoles(RoleSelectorScreen.AllRoles);
                    }
                }

                PlayerAttributesScreen.SetPlayerToDisplay(ActivePlayer);
                PlayerAttributesScreen.RenderPanel();

            RoleEfficiencyScreen.SetPlayerToDisplay(ActivePlayer);
            RoleEfficiencyScreen.RenderPanel();
           
            break;
        case App::ROLE_EDITOR:
            RoleSelectorScreen.RenderPanel();
            SaveRoleScreen.RenderPanel();
            break;
        case App::LOAD_FILES:
            CustomRoleLoaderScreen.RenderPanel();
            if (CustomRoleLoaderScreen.WasFileLoadedByUser())
            {
                // resetting the database
                RoleSelectorScreen.AllRoles = OriginalDB;
                UpdateRoleFromCustomFile(RoleSelectorScreen.AllRoles, CustomRoleLoaderScreen.GetFileToLoad());
            }
            ImGui::ShowDemoWindow();
            break;
        default:
            break;
        }


        // Rendering
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        // Update and Render additional Platform Windows
        // (Platform functions may change the current OpenGL context, so we save/restore it to make it easier to paste this code elsewhere.
        //  For this specific demo app we could also call glfwMakeContextCurrent(window) directly)
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            GLFWwindow* backup_current_context = glfwGetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            glfwMakeContextCurrent(backup_current_context);
        }

        glfwSwapBuffers(window);
    }
#ifdef __EMSCRIPTEN__
    EMSCRIPTEN_MAINLOOP_END;
#endif

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
