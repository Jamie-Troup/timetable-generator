#pragma once

#include <string>
#include <unordered_map>
#include <vector>

class Day
{
public:
	int										  day;
	int										  month; // zero indexed
	std::vector<int> 						  work_order; // vector of chapters to complete during this day
	std::unordered_map<int, std::vector<int>> work; // hashmap of chap num vs question numbers to complete during day
	
	Day(int day_in, int month_in);
	
	std::string print();
};
