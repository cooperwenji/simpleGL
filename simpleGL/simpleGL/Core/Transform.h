#pragma once

#include<string>
#include<sstream>

class Transform
{
public:
	static void int2str(const int &int_temp, std::string& string_temp)
	{
		std::stringstream stream;
		stream << int_temp;
		string_temp = stream.str();
	}

	static void str2int(int& int_temp, const std::string& string_temp)
	{
		std::stringstream stream(string_temp);
		stream >> int_temp;
	}
};
