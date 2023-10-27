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
    void SetName(const std::string& name);

    void SetCosmeticID(uint16_t id);
    uint16_t GetCosmeticID();

    uint64_t GetUniqueID();

    RoleEfficiency GetBestPlayerRole();

    void CalculateEfficiencyAllRoles(const std::vector<Role>& AllRoles);
    void UpdateEfficiency(const std::vector<Role>& AllRoles);

    std::vector <RoleEfficiency> GetDefensiveRoles();
    std::vector <RoleEfficiency> GetMidfieldRoles();
    std::vector <RoleEfficiency> GetAttackingRoles();

private:
    void SetUniqueID(const std::string&  filename);
    std::vector<Attribute> Attributes;
    std::string Name;
    
    uint16_t CosmeticID = 0;
    uint64_t UniqueID = 0;
    std::vector<RoleEfficiency> DefensiveRoles;
    std::vector<RoleEfficiency> MidfieldRoles;
    std::vector<RoleEfficiency> AttackingRoles;

    std::shared_ptr<RoleEfficiency> BestPlayerRole;

};
