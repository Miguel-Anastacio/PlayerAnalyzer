#include "RoleAnalysis.h"

float RoleAnalysis::CalculateRoleEfficiency(Role role, const std::vector<Attribute>& playerAtt)
{
    //int mainAttributesSum = 0;
    //int numberOfMainAttributes = 0;
    ////std::cout << role.Name << std::endl;
    ////std::cout << "Main Attributes" << std::endl;
    //for (auto& it : role.Attributes)
    //{
    //    if (it.Weight > 0.25)
    //    {
    //        for (auto& temp : playerAtt)
    //        {

    //            if (it.Name == temp.Name)
    //            {
    //                //std::cout << temp.Name << " " << temp.Value << std::endl;

    //                mainAttributesSum += temp.Value;
    //                numberOfMainAttributes++;
    //            }
    //        }
    //    }
    //}

    //float mainAttributeContribution = ((float)mainAttributesSum * 3) / ((float)numberOfMainAttributes * 20);
    ////std::cout << "Second Attributes" << std::endl;
    //int secondaryAttributesSum = 0;
    //int numberOfSecondaryAttributes = 0;
    //for (auto& it : role.Attributes)
    //{
    //    if (it.Weight < 0.25)
    //    {
    //        for (auto& temp : playerAtt)
    //        {
    //            if (it.Name == temp.Name)
    //            {
    //                //std::cout << temp.Name << " " << temp.Value << std::endl;
    //                secondaryAttributesSum += temp.Value;
    //                numberOfSecondaryAttributes++;
    //            }
    //        }
    //    }
    //}

    //float secondaryAttributeContribution = ((float)secondaryAttributesSum * 2) / ((float)numberOfSecondaryAttributes * 20);

    //return (mainAttributeContribution + secondaryAttributeContribution) / 5 * 100;
    float weightedAttributeSum = 0.0f;
    for (auto& att : role.Attributes)
    {
        for (auto& playerAttribute : playerAtt)
        {
            if (att.Name == playerAttribute.Name)
            {
                //std::cout << temp.Name << " " << temp.Value << std::endl;

                weightedAttributeSum += playerAttribute.Value * att.Weight;
                break;
            }
        }
    }

    return (weightedAttributeSum / (20 * role.TotalWeight)) * 100;

}
