#include "day.h"

#include <string>

Day::Day(int day_in, int month_in)
	: day(day_in), month(month_in)
{}

std::string Day::print()
{
	std::string string;
		
	for (auto& chapter : work_order)
	{
		auto temp_str = "Ch " + std::to_string(chapter) + " ";
		
		if (work[chapter][0] == -1)
		{
			temp_str += "Read, ";
		}
		else
		{
			// This section constructs a temp string for any non reading chapter and then adds this string to overall string
			std::string section_str;
			int last_val = -2; // can't be -1 as that is reading question num
			for (int i = 0; i < work[chapter].size(); i++)
			{
				auto val = work[chapter][i];
				if (last_val == -2)
				{
					last_val = val;
					section_str += std::to_string(val) + " ";
				}
				else
				{
					if (val - last_val != 1)
					{
						if (section_str.find_last_of("-") == (section_str.length() - 2))
						{
						 	section_str += std::to_string(last_val) + " && " + std::to_string(val) + " ";
						}
						else
						{
							section_str += "& " + std::to_string(val) + " ";				
						}
					}
					else
					{
						if (section_str.find_last_of("-") != (section_str.length() - 2))
						{
						 	section_str += "- ";
						}
						
						if (i == (work[chapter].size() - 1))
						{
							section_str += std::to_string(val);
						}
					}
					
				}
				
				last_val = val;
			}
			
			temp_str += section_str + ", ";
		}
		
		string += temp_str;
	}
	
	auto date_str = std::to_string(day) + "/" + std::to_string(month + 1) + ";";
	
	string = date_str + string;
	
	return string;
}
