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
class RoleEfficiencyPanel;
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
    void RenderMainMenuBar(RoleSelector& selector, SaveRolePanel& saveRole, Player* player, CustomRoleLoader& roleLoader, AppState& state, std::vector<Player>& allPlayers);
    //void RenderMainMenu();

    // UI Panels
 



    // helper to manage players loaded
    // returns -1 when is a new player
    // otherwise it returns an index
    static int IsPlayerAlreadyLoaded(const uint64_t& ID, std::vector<Player>& allPlayers);

    //Init UI Panels
    

    // operations to perform on UI panels when user navigates through the main menu bar;s
    void SwitchState(const AppState& newState, const std::vector<Role>& allRoles, Player* player = NULL, CustomRoleLoader* roleLoader = NULL, SaveRolePanel* roleSaver = NULL);
    //void SwitchState(const AppState& newState, const std::vector<Role>& allRoles, std::vector<std::shared_ptr<Player>>& allPlayers);


    std::vector<AttributeWeight> GetAttributesOfRole(uint64_t ID, const std::vector<Role>& allRoles);


    // Render Efficiency Screen
    void EfficiencyScreen(RoleEfficiencyPanel& efficiency, Player* player, const std::vector<Role>& roles);

}
