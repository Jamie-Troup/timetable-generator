#pragma once

#include "day.h"
#include "listnode.h"
#include "question.h"

#include <string>
#include <vector>
#include <unordered_map>

class Timetable
{
public:
	int 			 	    max_chap{};
	int 			 	    start_day{};
	int					    total_ques{};
	int					    daily_ques{};
	int 			 	    start_month{}; // zero indexed
	
	std::vector<Day>	    schedule;
	std::vector<int>&	    chap_ques;
	std::vector<int>&	    month_days;
	std::vector<int>&	    chap_order;
	std::vector<Question>   prob_ques;
	
	std::unordered_map<int, std::shared_ptr<ListNode>> chap_ques_map;
	std::unordered_map<int, std::vector<std::string>> alr_done_map;
	
	Timetable(int day, int month, int max_chap_in, std::vector<int>& chap_ques_in, int tot_ques, int ques_daily, std::vector<int>& chap_order_in, std::vector<int>& month_days_in);
	
	void print();
	void build_schedule(); // this takes the linked lists and transfers them into a daily schedule parameterised by the user
	void build_timetable(); // this builds each chapter's linked list of questions
	void add_prob_ques(Question ques);
	void add_alr_done(int chapter, std::vector<std::string> questions);
	void print_sched();
	void print_timetable();
	bool check_if_done(int ques_num, int chap);
};
