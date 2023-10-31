#pragma once
#include "glew.h"
#include "boilerplate.h"
#include <memory>
#include <vector>
#include "TextureManager.h"
#include "FileUploader.h"
struct Role;
class Player;
class RoleSelector;
class CustomRoleLoader;
class SaveRolePanel;
enum class AppState
{
    MAIN_MENU,
    ROLE_EDITOR,
    LOAD_FILES,
    PLAYER_COMPARISON
};

namespace PlayerAnalyzer
{
    // globals
    static GLFWwindow* Window;
    static const char* glsl_version;
    //static AppState State = AppState::MAIN_MENU;


    static bool InitGlfw();
    static void InitImGui();
    static void Cleanup();
    static void ResetRenderer();

    void Main();

    //void Run();
    void RenderMainMenuBar(RoleSelector& selector, SaveRolePanel& saveRole, std::shared_ptr<Player> player, CustomRoleLoader& roleLoader, AppState& state);
    //void RenderMainMenu();

    // UI Panels
 



    // helper to manage players loaded
    // returns -1 when is a new player
    // otherwise it returns an index
    static int IsPlayerAlreadyLoaded(const uint64_t& ID, const std::vector<std::shared_ptr<Player>>& allPlayers);

    //Init UI Panels
    

    // operations to perform on UI panels when user navigates through the main menu bar;s
    void SwitchState(const AppState& newState, const std::vector<Role>& allRoles, std::shared_ptr<Player> player = NULL, CustomRoleLoader* roleLoader = NULL, SaveRolePanel* roleSaver = NULL);

}