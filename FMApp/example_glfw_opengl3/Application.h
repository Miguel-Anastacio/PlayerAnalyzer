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
class PlayersLoaded;
class PlayerAttributesPanel;
class RoleEditor;
class SelectPlayers;
class PlayerAttributeComparison;
class Settings;
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
    static AppState State = AppState::MAIN_MENU;


    static bool InitGlfw();
    static void InitImGui();
    // poll glfw events, call Imgui new frame and enable dock space
    static void NewFrame();
    static void ImGuiRenderer();
    static void Cleanup();

    void Main();

    //void Run();
    void RenderMainMenuBar(RoleSelector& selector, SaveRolePanel& saveRole, Player* player, CustomRoleLoader& roleLoader, AppState& state, std::vector<Player>& allPlayers);
    //void RenderMainMenu();

    void InitDatabase(std::vector<Role>& out_AllRoles, std::vector<Role>& out_OriginalDB);
    void InitMainMenu(FileUploader& uploader, RoleEfficiencyPanel& efficiencyPanel, PlayersLoaded& loadedPlayersScreen, PlayerAttributesPanel& attributes,
                        const std::vector<Role>& allRoles, std::vector<Player>& allPlayers);
    void InitEditRolesMenu(RoleSelector& selector, RoleEditor& editor, std::vector<Role>& allRoles, std::vector<Role>& originalDB);

    void InitLoadFilesMenu(Settings& settings, RoleEfficiencyPanel& efficiencyPanel, PlayerAttributesPanel& attributes, RoleEditor& editor);

    void InitPlayerComparisonMenu(RoleSelector& selector, PlayerAttributeComparison& comparison, SelectPlayers& playersSelection, std::vector<Role>& allRoles,
                                        std::shared_ptr<Highlight<int>> highlight, std::vector<Player>& allPlayers);


    void RenderMainMenu(FileUploader& uploader, RoleEfficiencyPanel& efficiencyPanel, PlayersLoaded& loadedPlayersScreen, PlayerAttributesPanel& attributes,
        Player* activePlayer, std::vector<Player>& allPlayers, const std::vector<Role>& allRoles);

    void RenderEditRolesMenu(RoleSelector& selector, SaveRolePanel& roleSaver);

    void RenderLoadFilesMenu(Settings& settings, CustomRoleLoader& roleLoader, std::vector<Role>& allRoles, std::vector<Role>& originalDB);

    void RenderPlayerComparisonMenu(RoleSelector& selector, SelectPlayers& playerSelection, PlayerAttributeComparison& comparison);

    // helper to manage players loaded; returns -1 when is a new player otherwise it returns an index
    static int IsPlayerAlreadyLoaded(const uint64_t& ID, std::vector<Player>& allPlayers);

    //Init UI Panels
    

    // operations to perform on UI panels when user navigates through the main menu bar;s
    void SwitchState(const AppState& newState, const std::vector<Role>& allRoles, Player* player = NULL, CustomRoleLoader* roleLoader = NULL,
                        SaveRolePanel* roleSaver = NULL);
    //void SwitchState(const AppState& newState, const std::vector<Role>& allRoles, std::vector<std::shared_ptr<Player>>& allPlayers);


    std::vector<AttributeWeight> GetAttributesOfRole(uint64_t ID, const std::vector<Role>& allRoles);


    // Render Efficiency Screen
    void EfficiencyScreen(RoleEfficiencyPanel& efficiency, Player* player, const std::vector<Role>& roles);

}
