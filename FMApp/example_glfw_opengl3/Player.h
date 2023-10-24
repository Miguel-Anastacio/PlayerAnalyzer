#pragma once
#include "RoleAnalysis.h"
#include "Define.h"
class  Player
{
public:
    Player();
    ~Player();

    std::string ParseLine(const std::string& line, char separator, int& lineEndIndex);
    void CheckNextCharacters(int& position, const std::string& line);

    bool ReadAttributesFromFile(std::string FileName);

    std::vector <Attribute> GetPlayerAttributes();
    void ClearAttributes();

    std::string GetName();

    RoleEfficiency GetBestPlayerRole();

    void CalculateEfficiencyAllRoles(const std::vector<Role>& AllRoles);
    void UpdateEfficiency(const std::vector<Role>& AllRoles);

    std::vector <RoleEfficiency> GetDefensiveRoles();
    std::vector <RoleEfficiency> GetMidfieldRoles();
    std::vector <RoleEfficiency> GetAttackingRoles();

private:
    std::vector<Attribute> Attributes;
    std::string Name;
    std::vector<RoleEfficiency> DefensiveRoles;
    std::vector<RoleEfficiency> MidfieldRoles;
    std::vector<RoleEfficiency> AttackingRoles;

    std::shared_ptr<RoleEfficiency> BestPlayerRole;

};
