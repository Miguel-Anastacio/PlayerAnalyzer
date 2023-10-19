#pragma once
#include <fstream>
#include <iostream>
#include <list>
#include "json.hpp"

#include "Define.h"

using json = nlohmann::json;

std::vector<Role> BuildRoleDatabase();

void PrintArrayOfRoles(const std::vector<Role>& AllPlayerRoles);

void CleanUpDatabase(std::vector<Role>& AllPlayerRoles);

void WriteDatabaseFile(const std::vector<Role>& AllPlayerRoles);
