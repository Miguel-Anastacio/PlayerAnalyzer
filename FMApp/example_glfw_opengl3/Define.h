#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <map>
#include <vector>
const std::vector<std::string> AttributesNames = { "Acceleration",
                                                "Aggression",
                                                "Agility",
                                                "Anticipation",
                                                "Balance",
                                                "Bravery",
                                                "Composure",
                                                "Concentration",
                                                "Corners",
                                                "Crossing",
                                                "Decisions",
                                                "Determination",
                                                "Dribbling",
                                                "Finishing",
                                                "First Touch",
                                                "Flair",
                                                "Free Kick Taking",
                                                "Heading",
                                                "Jumping Reach",
                                                "Leadership",
                                                "Long Shots",
                                                "Long Throws",
                                                "Marking",
                                                "Natural Fitness",
                                                "Off The Ball",
                                                "Pace",
                                                "Passing",
                                                "Penalty Taking",
                                                "Positioning",
                                                "Stamina",
                                                "Strength",
                                                "Tackling",
                                                "Teamwork",
                                                "Technique",
                                                "Vision",
                                                "Work Rate" };

const std::vector<std::string> MentalAttributesNames = {
                                                "Aggression",
                                                "Anticipation",
                                                "Bravery",
                                                "Composure",
                                                "Concentration",
                                                "Decisions",
                                                "Determination",
                                                "Flair",
                                                "Leadership",
                                                "Off The Ball",
                                                "Positioning",
                                                "Teamwork",
                                                "Vision",
                                                "Work Rate" };

const std::vector<std::string> TechnicalAttributesNames = {
                                                "Corners",
                                                "Crossing",
                                                "Dribbling",
                                                "Finishing",
                                                "First Touch",
                                                "Free Kick Taking",
                                                "Heading",
                                                "Long Shots",
                                                "Long Throws",
                                                "Marking",
                                                "Passing",
                                                "Penalty Taking",
                                                "Tackling",
                                                "Technique"
                                              };
const std::vector<std::string> PhysicalAttributesNames = {
                                                "Acceleration",
                                                "Agility",
                                                "Balance",
                                                "Jumping Reach",
                                                "Natural Fitness",
                                                "Pace",
                                                "Stamina",
                                                "Strength" };

enum AttributeType
{
    Technical,
    Mental,
    Physical
};


struct Attribute
{
    int Value = 0;
    std::string Name = "Null";
    AttributeType Type;
    void ClampValue()
    {
        if (Value > 20)
        {
            Value = 20;
        }
        else if (Value < 20)
        {
            Value = 0;
        }
    }
    void AssignType(std::string name)
    {
        for (auto& temp : TechnicalAttributesNames)
        {
            if (temp == name)
            {
                Type = Technical;
            }
        }
        for (auto& temp : MentalAttributesNames)
        {
            if (temp == name)
            {
                Type = Mental;
            }
        }
        for (auto& temp : PhysicalAttributesNames)
        {
            if (temp == name)
            {
                Type = Physical;
            }
        }
    }

    bool IsValidName(std::string name)
    {
        for (auto& it : AttributesNames)
        {
            if (it == name)
            {
                AssignType(name);
                return true;
            }
        }
        return false;
    }

};

enum RoleType
{
    Defensive,
    Midfield,
    Attacking
};

struct AttributeWeight
{
    std::string Name = "Default";
    float Weight = 0.0f;
    AttributeType Type;

    void AssignType(std::string name)
    {
        for (auto& temp : TechnicalAttributesNames)
        {
            if (temp == name)
            {
                Type = Technical;
            }
        }
        for (auto& temp : MentalAttributesNames)
        {
            if (temp == name)
            {
                Type = Mental;
            }
        }
        for (auto& temp : PhysicalAttributesNames)
        {
            if (temp == name)
            {
                Type = Physical;
            }
        }
    }

    AttributeWeight(std::string name, float value) : Name(name), Weight(value) {
    }
};


struct Role
{
    std::string Type = "Default";
    RoleType TypeEnum;
    std::vector<AttributeWeight> Attributes;

    std::string Name = "Role";

    float TotalWeight = 0;


    void SetType(const std::string& type)
    {
        Type = type;
        if (type == "Defensive")
            TypeEnum = Defensive;
        else if (type == "Midfield")
            TypeEnum = Midfield;
        else if (type == "Attacking")
            TypeEnum = Attacking;
        else
            std::cerr << "Invalid Role Type";
    }

    void AddAttributeFromFile(std::string name, std::string category)
    {
        float weight = 0;
        if (category == "prefer")
        {
            weight = 0.2f;
        }
        else if (category == "vital")
        {
            weight = 0.3f;
        }
        Attributes.emplace_back(name, weight);
        TotalWeight += weight;
    }
};


struct RoleEfficiency
{
    std::string RoleName = "Default";
    float Value = 0;

    RoleEfficiency(std::string name, float value) : RoleName(name), Value(value) {
    }
    RoleEfficiency() {
    }

};
