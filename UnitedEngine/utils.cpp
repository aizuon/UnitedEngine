#include "utils.hpp"

#include <sstream>
#include <Windows.h>

std::string to_string(uint32_t number)
{
	std::stringstream ss;
	ss << number;

	return ss.str();
}

std::string round(double d, int decimals)
{
	std::string result;
	std::stringstream sx;
	sx << std::fixed << d;
	result = sx.str();

	size_t pos = result.find('.');
	if (pos == std::string::npos)
		return result;
	if (!decimals)
	{
		return result.substr(0, pos);
	}
	if (pos + decimals + 1 < result.size())
	{
		return result.substr(0, pos + decimals + 1);
	}

	return result;
}

std::vector<char> load_png(int resource_id)
{
	return load_resource(resource_id, "PNG");
}

std::vector<char> load_font(int resource_id)
{
	return load_resource(resource_id, "xfont");
}

std::vector<char> load_resource(int resource_id, const std::string& resource_type)
{
	HRSRC hResource = FindResource(NULL, MAKEINTRESOURCE(resource_id), resource_type.c_str());
	HGLOBAL hMemory = LoadResource(NULL, hResource);
	DWORD dwSize = SizeofResource(NULL, hResource);
	LPVOID lpAddress = LockResource(hMemory);

	std::vector<char> bytes;
	bytes.resize(dwSize);
	memcpy(bytes.data(), lpAddress, dwSize);

	return bytes;
}
