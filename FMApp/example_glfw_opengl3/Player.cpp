#include "Player.h"

Player::Player()
{

}

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
            char debug = line.at(temp);
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


bool Player::ReadAttributesFromFile(std::string FileName)
{
    std::ifstream file(FileName);  // Replace "your_file.txt" with the actual file path

    Name = FileName;

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

    // Display the parsed data
    for (const auto& it : Attributes)
    {
        //std::cout << it.Name << " " << it.Value << std::endl;
    }

    //return 0;
    return true;
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

RoleEfficiency Player::GetBestPlayerRole()
{
    return *BestPlayerRole;
}

void Player::CalculateEfficiencyAllRoles(const std::vector<Role>& AllRoles)
{
    for (auto& it : AllRoles)
    {
        float efficiency = RoleAnalysis::CalculateRoleEfficiency(it, Attributes);

        if (BestPlayerRole == nullptr)
        {
            BestPlayerRole = std::make_shared<RoleEfficiency>();
        }
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

        std::cout << Name << " efficiencey at " << it.Name << ": " << efficiency << std::endl;
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