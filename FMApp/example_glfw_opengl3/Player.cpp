#include "Player.h"

Player::Player()
{

}

//Player::Player(const Player& pl)
//{
//    Attributes = pl.Attributes;
//    Name = pl.Name;
//
//    CosmeticID = pl.CosmeticID;
//    UniqueID = pl.UniqueID;
//    DefensiveRoles = pl.DefensiveRoles;
//    MidfieldRoles = pl.MidfieldRoles;
//    AttackingRoles = pl.AttackingRoles;
//
//    BestPlayerRole = pl.BestPlayerRole;
//}

Player::~Player()
{

}
void Player::CheckNextCharacters(int& position, const std::string& line)
{
    bool spaceFound = false;
    int temp = position;
    int trueEndPos = position;
    while (temp < line.size())
    {
        if (line.at(temp) != ' ')
        {
            if (spaceFound)
                spaceFound = false;
        }
        else
        {
            if (spaceFound)
            {
                trueEndPos = temp - 1;
                position = trueEndPos;
                return;
            }
            spaceFound = true;
        }
        temp++;
    }

}



std::string Player::ParseLine(const std::string& line, char separator, int& lineEndIndex)
{
    // get inital and end positions of relevant data
    int startPos = line.find(separator, lineEndIndex);
    if (startPos == std::string::npos)
        return NULL;
    int endPos = line.find(separator, startPos + 1);
    if (endPos == std::string::npos)
        return NULL;
    // take a look at the next characters to see if it is the case that the attribute has more than one word
    CheckNextCharacters(endPos, line);

    int stringSize = (endPos)-(startPos + 1);
    lineEndIndex = endPos;
    return line.substr(startPos + 1, stringSize);
}


bool Player::ReadAttributesFromFile(std::string fileName)
{
    Name = fileName.substr(fileName.find_last_of("\\") + 1);
    std::ifstream file(fileName);  // Replace "your_file.txt" with the actual file path

    SetUniqueID(Name);

    if (file.is_open())
    {
        std::string line;

        while (std::getline(file, line))
        {
            int index = line.find('|');
            // This line contains data
            if (index != std::string::npos)
            {
                Attribute aux;
                std::string name = ParseLine(line, ' ', index);
                if (aux.IsValidName(name))
                {
                    aux.Name = name;
                    int startValuePos = line.find('|', index);
                    int temp = startValuePos;
                    // go through every character and find the first that is not a '|' or a ' '
                    while (temp < line.size())
                    {
                        temp++;
                        if (line.at(temp) != '|' && line.at(temp) != ' ')
                        {
                            startValuePos = temp;
                            break;
                        }
                    }
                    int endValuePos = startValuePos;
                    CheckNextCharacters(endValuePos, line);
                    std::string tempValueString = line.substr(startValuePos, endValuePos - startValuePos);
                    try {
                        aux.Value = std::stoi(tempValueString);
                        aux.HashAttribute();
                        Attributes.push_back(aux);
                    }
                    catch (std::invalid_argument const& ex) {
                        std::cerr << "Invalid argument: " << ex.what() << std::endl;
                    }
                    catch (std::out_of_range const& ex) {
                        std::cerr << "Out of range: " << ex.what() << std::endl;
                    }
                }
            }
            else if (!line.empty()) {

            }
        }

        // Close the file after reading
        file.close();
    }
    else {
        std::cerr << "Error: Unable to open the file." << std::endl;
        return false;
        //return 1;  // Exit with an error code
    }

    //// Display the parsed data
    //for (const auto& it : Attributes)
    //{
    //    //std::cout << it.Name << " " << it.Value << std::endl;
    //}

    if (Attributes.size() > 0)
        return true;
    else
        return false;

    //return 0;
}

std::vector <Attribute> Player::GetPlayerAttributes()
{
    return Attributes;
}

void Player::ClearAttributes()
{
    Attributes.clear();
}

std::string Player::GetName()
{
    return Name;
}

void Player::SetName(const std::string& name)
{
    Name = name;
}

void Player::SetCosmeticID(uint16_t id)
{
    CosmeticID = id;
    Name = Name + std::to_string(id);
}

uint16_t Player::GetCosmeticID()
{
    return CosmeticID;
}

uint64_t Player::GetUniqueID()
{
    return UniqueID;
}

RoleEfficiency Player::GetBestPlayerRole()
{
    return *BestPlayerRole;
}

void Player::CalculateEfficiencyAllRoles(const std::vector<Role>& AllRoles)
{
    if (BestPlayerRole == nullptr)
    {
        BestPlayerRole = std::make_shared<RoleEfficiency>();
    }

    for (auto& it : AllRoles)
    {
        float efficiency = RoleAnalysis::CalculateRoleEfficiency(it, Attributes);

        if (efficiency > BestPlayerRole->Value)
        {
            BestPlayerRole->RoleName = it.Name;
            BestPlayerRole->Value = efficiency;
        }

        switch (it.TypeEnum)
        {
        case Defensive:
            DefensiveRoles.emplace_back(it.Name, RoleAnalysis::CalculateRoleEfficiency(it, Attributes));
            break;
        case Midfield:
            MidfieldRoles.emplace_back(it.Name, RoleAnalysis::CalculateRoleEfficiency(it, Attributes));
            break;
        case Attacking:
            AttackingRoles.emplace_back(it.Name, RoleAnalysis::CalculateRoleEfficiency(it, Attributes));
            break;
        default:
            break;
        }
//        std::cout << Name << " efficiencey at " << it.Name << ": " << efficiency << std::endl;
    }
}

void Player::UpdateEfficiency(const std::vector<Role>& AllRoles)
{
    if (BestPlayerRole == nullptr)
    {
        BestPlayerRole = std::make_shared<RoleEfficiency>();
    }
    else
    {
        BestPlayerRole->RoleName = "";
        BestPlayerRole->Value = 0;
    }

    for (auto& it : AllRoles)
    {
        float efficiency = RoleAnalysis::CalculateRoleEfficiency(it, Attributes);

        
        if (efficiency > BestPlayerRole->Value)
        {
            BestPlayerRole->RoleName = it.Name;
            BestPlayerRole->Value = efficiency;
        }



        switch (it.TypeEnum)
        {
        case Defensive:
            for (auto& defEfficiency : DefensiveRoles)
            {
                if (it.ID == defEfficiency.ID)
                {
                    defEfficiency.Value = efficiency;
                    break;
                }
            }
            break;
        case Midfield:
            for (auto& midEfficiency : MidfieldRoles)
            {
                if (it.ID == midEfficiency.ID)
                {
                    midEfficiency.Value = efficiency;
                    break;
                }
            }
            break;
        case Attacking:
            for (auto& attackEfficiency : AttackingRoles)
            {
                if (it.ID == attackEfficiency.ID)
                {
                    attackEfficiency.Value = efficiency;
                    break;
                }
            }
            break;
        default:
            break;
        }

    }
}

std::vector<RoleEfficiency> Player::GetDefensiveRoles()
{
    return DefensiveRoles;
}

std::vector<RoleEfficiency> Player::GetMidfieldRoles()
{
    return MidfieldRoles;
}

std::vector<RoleEfficiency> Player::GetAttackingRoles()
{
    return AttackingRoles;
}

RoleEfficiency Player::GetEfficiencyOfRole(const uint64_t& ID)
{
    for (const auto& def : DefensiveRoles)
    {
        if (def.ID == ID)
        {
            return def;
        }
    }

    for (const auto& mid : MidfieldRoles)
    {
        if (mid.ID == ID)
        {
            return mid;
        }
    }

    for (const auto& off : AttackingRoles)
    {
        if (off.ID == ID)
        {
            return off;
        }
    }
}

RoleEfficiency Player::GetEfficiencyOfRole(const uint64_t& ID, const RoleType& type)
{
    switch (type)
    {
    case Defensive:
        for (const auto& role : DefensiveRoles)
        {
            if (role.ID == ID)
            {
                return role;
            }
        }
        break;
    case Midfield:
        for (const auto& role : MidfieldRoles)
        {
            if (role.ID == ID)
            {
                return role;
            }
        }
        break;
    case Attacking:
        for (const auto& role : AttackingRoles)
        {
            if (role.ID == ID)
            {
                return role;
            }
        }
        break;

    default:
        break;
    }

}

void Player::SetUniqueID(const std::string& filename)
{
    UniqueID = std::hash<std::string>{}(filename);
}
