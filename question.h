#pragma once

class Question
{
public:
	int num		   {};
	int chap_num = {};
	int chap_req = -1;
	
	Question(int q, int chap)
		: num(q), chap_num(chap) 
	{}
	
	Question(int q, int chap, int cond)
		: num(q), chap_num(chap), chap_req(cond)
	{}
};
