#include "Player.h"
#include "CustomRoleLoader.h"
namespace App
{
    enum AppState
    {
        MAIN_MENU,
        ROLE_EDITOR,
        LOAD_FILES
    };

    AppState State = MAIN_MENU;

    void SwitchState(const AppState& newState, const std::vector<Role>& allRoles, std::shared_ptr<Player> player = NULL, CustomRoleLoader* roleLoader = NULL)
    {
        switch (newState)
        {
            case MAIN_MENU:
                if (player != NULL)
                {
                    player->CalculateEfficiencyAllRoles(allRoles);
                }
                break;
            case ROLE_EDITOR:
                break;
            case LOAD_FILES:
                if (roleLoader != NULL)
                {
                    roleLoader->ClearFiles();
                    roleLoader->GetFilesInDirectory("custom_roles");
                }

                break;
            default:
            break;
        }
        State = newState;
    }


}
