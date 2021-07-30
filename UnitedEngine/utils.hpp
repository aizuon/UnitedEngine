#pragma once

#include <string>
#include <vector>

std::string to_string(uint32_t number);
std::string round(double d, int decimals);
std::vector<char> load_png(int resource_id);
std::vector<char> load_font(int resource_id);
std::vector<char> load_resource(int resource_id, const std::string& resource_type);
