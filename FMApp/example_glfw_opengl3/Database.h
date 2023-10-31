#pragma once
#include <fstream>
#include <iostream>
#include <filesystem>
#include <list>
#include "json.hpp"

#include "Define.h"

using json = nlohmann::json;

std::vector<Role> BuildRoleDatabase();

void PrintArrayOfRoles(const std::vector<Role>& AllPlayerRoles);

void CleanUpDatabase(std::vector<Role>& AllPlayerRoles);

bool WriteRoleWeightsFile(const Role& role, const std::string& fileName);

void UpdateRoleFromCustomFile(std::vector<Role>& AllRoles, const std::string& fileName);

// used to create the preview
// it reads the file name provided from the folder custom_roles
// outputs a vector that contains the name of all roles edited by the file
std::vector<std::string> ReadRolesEditedByFile(const std::string& fileName, const std::vector<Role>& AllRoles);


