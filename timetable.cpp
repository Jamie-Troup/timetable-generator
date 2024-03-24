#include "timetable.h"

#include "day.h"
#include "listnode.h"
#include "question.h"

#include <algorithm>
#include <iostream>
#include <memory>
#include <string>

Timetable::Timetable(int day, int month, int max_chap_in, std::vector<int>& chap_ques_in, int tot_ques, int ques_daily, std::vector<int>& chap_order_in, std::vector<int>& month_days_in)
	: max_chap(max_chap_in),
	  start_day(day),
	  start_month(month),
	  chap_ques(chap_ques_in),
	  total_ques(tot_ques),
	  daily_ques(ques_daily),
	  chap_order(chap_order_in),
	  month_days(month_days_in)
{}
		
void Timetable::build_timetable()
{
	for (int i=1; i <= max_chap; i++)
	{
		std::shared_ptr<ListNode> head;
		if (chap_ques[i] == -1)
		{
			auto new_node = std::make_shared<ListNode>();
			new_node->question = std::make_shared<Question>(-1, i);
			chap_ques_map[i] = new_node;
		}
		else
		{
			for (int j=1; j <= chap_ques[i]; j++)
			{
				auto new_node = std::make_shared<ListNode>();
				new_node->question = std::make_shared<Question>(j, i);
				if (check_if_done(j, i) == false)
				{
					if (chap_ques_map.count(i) == 0)
					{
						chap_ques_map[i] = new_node;
						head = new_node;
					}
					else
					{
						head->next = new_node;
						head = head->next;
					}
				}
			}
		}
	}

	for (auto& problem : prob_ques)
	{
		auto head = chap_ques_map[problem.chap_num];
		int count = 0;
		bool ques_found = false;
		
		while (!ques_found)
		{
			if (head->question->num == problem.num)
			{
				ques_found = true;
			}
			else
			{
				head = head->next;
				count++;
			}
		}
		
		if (count == 0 && head->next == nullptr)
		{
			chap_ques_map[problem.chap_num] = nullptr;
		}
		else if (count == 0)
		{
			chap_ques_map[problem.chap_num] = chap_ques_map[problem.chap_num]->next;
		}
		else
		{
			auto head_2 = chap_ques_map[problem.chap_num];
			
			for (int i=0; i < (count -1); i++)
			{
				head_2 = head_2->next;
			}
			
			if (head->next == nullptr)
			{
				head_2->next = nullptr;
			}
			else
			{
				head_2->next = head->next;
			}
		}
		
		auto head_3 = chap_ques_map[problem.chap_req];
		
		for (head_3; head_3->next != nullptr; head_3 = head_3->next) {}
		head_3->next = head;
		head->next = nullptr;
	}
}

void Timetable::print_timetable()
{
	for (int j = 0; j <= max_chap; j++)
	{
		if (chap_ques_map[j])
		{
			for (auto head = chap_ques_map[j]; head; head = head->next)
			{
				std::cout << "Chapter: " << head->question->chap_num << " Question: " << head->question->num << std::endl;
			}
		}
	}
}

bool Timetable::check_if_done(int ques_num, int chap)
{
	if (alr_done_map.count(chap) != 0)
	{
		for (int i = 0; i < alr_done_map[chap].size(); i++)
		{
			std::string string = alr_done_map[chap][i];
			if (string.length() == 1)
			{
				if (ques_num == std::stoi(string))
				{
					return true;
				}
			}
			else
			{
				std::string back = string.substr(string.find("-")+1);
				std::string front = string.substr(0, string.find("-"));
				
				if (ques_num <= std::stoi(back) && ques_num >= std::stoi(front))
				{
					return true;
				}
			}
		}
		
		return false;
	}
	else
	{
		return false;
	}
}

void Timetable::add_prob_ques(Question ques)
{
	prob_ques.push_back(ques);
}

void Timetable::build_schedule()
{
	int  chap_ind = 0;
	int  ques_done = 0;
	int  chap_count = 1;
	int  daily_ques_done = 0;
	int  chap_num = chap_order[chap_ind];
	auto curr_day = Day(start_day, start_month);
	
	for (int i = 0; i <= chap_order.size(); i++)
	{
		auto val = chap_order[i];
		if (chap_ques_map[val])
		{
			auto head = chap_ques_map[val];
			auto loop = true;
			
			for (head; loop == true; head = head->next)
			{
				if (daily_ques_done >= daily_ques)
				{
					schedule.push_back(curr_day);
					
					if (curr_day.day == month_days[curr_day.month])
					{
						curr_day = Day(1, curr_day.month + 1);			
					}
					else
					{
						curr_day = Day(curr_day.day + 1, curr_day.month);
					}
					
					daily_ques_done = 0;
				}
				
				if (head->question->num == -1)
				{
					curr_day.work[head->question->chap_num].push_back(-1);
					daily_ques_done += 5;
				}
				else
				{
					curr_day.work[head->question->chap_num].push_back(head->question->num);		
				}
				
				auto vec = curr_day.work_order;
				
				if (std::find(vec.begin(), vec.end(), head->question->chap_num) == vec.end())
				{
					curr_day.work_order.push_back(head->question->chap_num);				
				}
				
				daily_ques_done++;
				
				if (head->next == nullptr)
				{
					loop = false;
				} 
			}
		}
	}
}

void Timetable::print_sched()
{
	for (auto& day : schedule)
	{
		std::cout << day.print() << std::endl;
	}
}

void Timetable::add_alr_done(int chapter, std::vector<std::string> questions)
{
	alr_done_map[chapter] = questions;
}
