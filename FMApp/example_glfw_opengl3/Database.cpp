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
                        tempRole.HashRole();
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

void WriteRoleWeightsFile(const Role& Role, const std::string& fileName)
{
    std::filesystem::path folderPath = "custom_roles"; // Set the desired folder name here
    std::string name = fileName + ".txt";
    std::filesystem::path filePath = folderPath / name;
    try
    {
        if (std::filesystem::create_directory(folderPath))
        {
            std::cout << "Folder created successfully." << std::endl;
        }
        else {
            std::cout << "Folder already exists or an error occurred." << std::endl;
        }
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    std::ofstream file;
    file.open(filePath, std::ios::out | std::ios::app);

    if (file.is_open())
    {

        file <<"ID," << Role.ID << std::endl;
        for (const auto& att : Role.Attributes)
        {
            file << att.ID << "," << att.Name << "," << att.Weight << std::endl;
        }
        file.close();
    }

    //std::ofstream outfile(filePath, std::ios::out);
    //
    ////file.open(filePath);
    //if (outfile.is_open())
    //{
    //    outfile << Role.Name << std::endl;
    //    for (const auto& att : Role.Attributes)
    //    {
    //        outfile << att.Name << "," << att.Weight << std::endl;
    //    }
    //    //file.write(Role.Name.c_str(), Role.Name.size());
    //    outfile.close();
    //}
}

void UpdateRoleFromCustomFile(std::vector<Role>& AllRoles, const std::string& fileName)
{
    std::filesystem::path folderPath = "custom_roles"; // Set the desired folder name here
    std::filesystem::path filePath = folderPath / fileName;
    std::ifstream file(filePath);  

    if (file.is_open())
    {
        Role* RoleToEdit = NULL;
        std::string line;
        uint64_t currentId;

        while (std::getline(file, line))
        {
            // check if line contains an ID
            if (line.find("ID") == 0)
            {
   
                try
                {
                    currentId = std::stoull(line.substr(3));
                }
                catch (const std::invalid_argument& e) {
                    std::cerr << "Invalid argument: " << e.what() << std::endl;
                }
                catch (const std::out_of_range& e) {
                    std::cerr << "Out of range: " << e.what() << std::endl;
                    std::cerr << "Problematic string: " << currentId << std::endl;
                }
                // Extract the ID
                for (auto& role : AllRoles)
                {
                    if (role.ID == currentId)
                    {
                        RoleToEdit = &role;
                    }

                }

            }
            else
            {
                // This line contains data
                size_t posName = line.find(",");
                if (posName != std::string::npos)
                {
                    size_t posValue = line.find(",", posName+1);

                    // update database
                    

                    std::string NameAtt = line.substr(posName + 1,posValue - 1 - posName);

                    float value = std::stof(line.substr(posValue+1));
                    size_t attributeID = std::stoull(line.substr(0,posName));

                    int index = RoleToEdit->GetAttributeIndex(attributeID);
                    if (index != -1)
                    {
                        RoleToEdit->Attributes[index].Weight = value;
                        RoleToEdit->CalculateTotalWeight();
                    }
                    else
                    {
                        RoleToEdit->Attributes.emplace_back(NameAtt, value);
                        RoleToEdit->CalculateTotalWeight();
                    }

                }
            }
        }
    
    }
    else
    {
        std::cerr << "Error: Unable to open the file." << std::endl;
        //return 1;  // Exit with an error code
    }
}


