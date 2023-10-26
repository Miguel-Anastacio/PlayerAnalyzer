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


