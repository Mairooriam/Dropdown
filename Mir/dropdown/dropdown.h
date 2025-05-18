
#pragma once
#include <string>
#include <vector>

#include "imgui.h"
#include "misc/cpp/imgui_stdlib.h" // stdlib support

namespace Mir{
    void Dropdown(std::string& _str, const std::string& _id, const std::vector<std::string>& _options); 
}

