#pragma once

#include "question.h"

#include <memory>

class ListNode
{
public:
	std::shared_ptr<ListNode> next;
	std::shared_ptr<Question> question;
	
	ListNode() {}
	
	ListNode(Question quest_in)
	{
		question = std::make_shared<Question>(quest_in);
	}
};
