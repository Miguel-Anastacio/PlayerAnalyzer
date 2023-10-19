#include "Database.h"

std::vector<Role> BuildRoleDatabase()
{
    std::vector<Role> Database;

    // Read JSON from a file
    std::ifstream file("atom.json");
    json jsonData;
    file >> jsonData;
    // Iterate through the top-level objects
    for (auto& roleType : jsonData.items())
    {
        for (auto& role : roleType.value().items())
        {
            //std::cout << "Position: " << role.key() << std::endl;
            // Iterate through Attack, Support, and Defend for each position
            for (auto& status : role.value().items())
            {
                Role tempRole;
                tempRole.SetType(roleType.key());
             

                tempRole.Name = role.key();
                // std::cout << "  Role: " << role.key() << std::endl;
                tempRole.Name = tempRole.Name + " on " + status.key();

                // Iterate through vital and prefer for each role
                for (auto& category : status.value().items())
                {
                    // Iterate through vital and prefer arrays
                    for (const auto& skill : category.value())
                    {
                        std::string aux = category.key();
                        tempRole.AddAttributeFromFile(skill, category.key());

                    }
                }
                
                Database.emplace_back(tempRole);
            }

        }
    }
    return Database;
}

void PrintArrayOfRoles(const std::vector<Role>& AllPlayerRoles)
{
    for (auto& it : AllPlayerRoles)
    {
        std::cout << "Role Type --- " << it.Type << std::endl;
        std::cout << "Role: " << it.Name << std::endl;
        std::cout <<  std::endl;
        ////std::cout << "Attributes " << std::endl;
        ////std::cout << "  Vital: " << std::endl;
        //for (auto aux : it.MainAttributes)
        //{
        //    //std::cout << "      " << aux << std::endl;
        //}
        //std::cout << "  Prefered: " << std::endl;
        //for (auto aux : it.SecondaryAttributes)
        //{
        //    std::cout << "      " << aux << std::endl;
        //}
    }
}

void CleanUpDatabase(std::vector<Role>& AllPlayerRoles)
{
    for (std::vector<Role>::iterator it = AllPlayerRoles.begin(); it != AllPlayerRoles.end();)
    {
        if (it->Attributes.size() < 2)
        {
            it = AllPlayerRoles.erase(it);
        }
        else
        {
            ++it;
        }
    }
}

// this is pointless...
void WriteDatabaseFile(const std::list<Role>& AllPlayerRoles)
{

    std::ofstream myfile;
    myfile.open("example.txt");
    for (auto& it : AllPlayerRoles)
    {
        std::cout << it.Name << std::endl;
        std::cout << "Main Attributes " << std::endl;
        for (auto& aux : it.Attributes)
        {
            std::cout << aux.Name << std::endl;
        }
        std::cout << "Secondary Attributes: " << std::endl;
        for (auto& aux : it.Attributes)
        {
            std::cout << "      " << aux.Name << std::endl;
        }
    }

    myfile.close();
}
